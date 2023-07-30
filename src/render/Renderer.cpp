#include "draw/Renderer.h"
#include <stdio.h>
#include "core/Engine.h"
#include "core/Window.h"
#include "colors/Colors.h"
#include "mesh/Mesh.h"
#include "vectors/VectorMath.h"
#include "matrix/Matrix.h"

Renderer::Renderer()
	:renderer(nullptr), fps(30), targetFrameTime(1000 / fps), colorBufferTexture(nullptr), utility(this), 
	scene(Engine::GetInstance()->GetScene())
{

}

Renderer::~Renderer()
{
	SDL_DestroyRenderer(renderer);
}


bool Renderer::CreateRenderer()
{
	SDL_Window* window = Engine::GetInstance()->GetWindow()->GetSdlWindow();
	renderer = SDL_CreateRenderer(window, -1, 0);
	if (!renderer)
	{
		fprintf(stderr, "Error Creating SDL Renderer. \n");
		return false;
	}

	return true;
}

/* Color buffer is not actually displayed, it will be moved to an SDL_Texture to be displayed.*/
void Renderer::ClearColorBuffer(uint32_t color)
{
	for (int y = 0; y < GetWindowHeight(); y++)
	{
		for (int x = 0; x < GetWindowWidth(); x++)
		{
			colorBuffer[(GetWindowWidth() * y) + x] = color;
		}
	}
}

/* Copy the color buffer into the SDL_Texture to be displayed. */
void Renderer::RenderColorBuffer()
{
	SDL_UpdateTexture(colorBufferTexture, NULL, colorBuffer.data(), GetWindowWidth() * sizeof(uint32_t));
	SDL_RenderCopy(renderer, colorBufferTexture, NULL, NULL);
	const char* error = SDL_GetError();
	if (*error) {
		printf("SDL Error: %s\n", error);
		SDL_ClearError();
	}
}

const int Renderer::GetWindowHeight() const
{
	return 	Engine::GetInstance()->GetWindow()->GetHeight();
}

const int Renderer::GetWindowWidth() const
{
	return Engine::GetInstance()->GetWindow()->GetWidth();
}

void Renderer::AddToColorBuffer(int index, uint32_t color)
{
	try 
	{
		colorBuffer.at(index) = color;
	}
	catch (std::out_of_range& e) 
	{
		std::cerr << "Out of Range error: " << e.what() << '\n';
	}
}

void Renderer::Update()
{
	if (!scene)
	{
		std::cout << "No scene found.\n";
		return;
	}

	SDL_Delay(targetFrameTime);

	//utility.DrawTriangleWireFrame(20, 20, 100, 300, 200, 20, RED);

	/* ======================= NEEDS TO BE ABSTRACTED FROM HERE ===============================*/
	// Reset to NULL on every update;
	scene->EmptyTrianlgesToRender();

	/* I think later this can loop over all meshes in scene and render each. */
	Mesh* meshToRender = scene->GetMesh("Default Cube");
	if (!meshToRender)
	{
		std::cout << "Mesh to render is null\n";
		return;
	}
	
// 	float xRotation = meshToRender->GetRotation().x;
// 	float yRotation = meshToRender->GetRotation().y;
// 	float zRotation = meshToRender->GetRotation().z;
// 	meshToRender->SetRotation(Vector3D(xRotation + .01, yRotation + .01, zRotation + .01));
	
	Matrix4x4 scaleMatrix = MatrixMath::MakeScaleMatrix(meshToRender->GetScale());
	Matrix4x4 rotationMatrix_X = MatrixMath::MakeRotationMatrix_X(meshToRender->GetRotation().x);
	Matrix4x4 rotationMatrix_Y = MatrixMath::MakeRotationMatrix_Y(meshToRender->GetRotation().y);
	Matrix4x4 rotationMatrix_Z = MatrixMath::MakeRotationMatrix_Z(meshToRender->GetRotation().z);
	Matrix4x4 translationMatrix = MatrixMath::MakeTranslationMatrix(meshToRender->GetTranslation());

	for (int i = 0; i < meshToRender->GetFaces().size() - 1; i++)
	{
		Face currentFace = meshToRender->GetFaces()[i];

		std::array<Vector3D, 3> faceVertices;
		faceVertices[0] = meshToRender->GetVertices()[currentFace.GetIndices()[0] - 1];
		faceVertices[1] = meshToRender->GetVertices()[currentFace.GetIndices()[1] - 1];
		faceVertices[2] = meshToRender->GetVertices()[currentFace.GetIndices()[2] - 1];
		//currentFace.SetColor();

		/* Transform */
		std::array<Vector4D, 3> transformedVertices;
		for (int j = 0; j < transformedVertices.size() - 1; j++)
		{
			Vector4D transformedVertex = VectorMath::Vector3ToVector4(faceVertices[j]);

			transformedVertex = scaleMatrix * transformedVertex;
			transformedVertex = rotationMatrix_X * transformedVertex;
			transformedVertex = rotationMatrix_Y * transformedVertex;
			transformedVertex = rotationMatrix_Z * transformedVertex;
			transformedVertex = translationMatrix * transformedVertex;

			// Translate vertex away from camera
			if (scene->GetViewportCamera())
			{
				transformedVertex.z += scene->GetViewportCamera()->GetCameraLocation().z;
			}
			transformedVertices[j] = transformedVertex;
		}

		bool shouldProject = true;
		if (backFaceCullingEnabled)
		{
			shouldProject = utility.ShouldCullFace(transformedVertices);
		}

		/* Project */
		if (shouldProject)
		{
			std::array<Vector2D, 3> coordinatesToProject;
			for (int j = 0; j < coordinatesToProject.size() - 1; j++)
			{
				// project current vertex
				coordinatesToProject[j] = utility.Project(transformedVertices[j]);

				/* Move to middle of screen */
				coordinatesToProject[j].x += (Engine::GetInstance()->GetWindow()->GetWidth() / 2);
				coordinatesToProject[j].y += (Engine::GetInstance()->GetWindow()->GetHeight() / 2);
			}

			/* Replace with a z buffer */
			float faceDepth = (transformedVertices[0].z + transformedVertices[1].z + transformedVertices[2].z) / 3.0;

			Triangle triangleToProject (
				std::array<Vector2D, 3> {
					Vector2D(coordinatesToProject[0]), 
					Vector2D(coordinatesToProject[1]), 
					Vector2D(coordinatesToProject[2])
				},
				currentFace.GetColor(),
				faceDepth
			);
			scene->AddTriangleToRender(triangleToProject);
		}

		/* Replace with a z buffer */
		for (int i = 0; i < scene->GetTrianglesToRender().size() - 1; i++)
		{
			for (int j = i; j < scene->GetTrianglesToRender().size() - 1; j++)
			{
				if (scene->GetTrianglesToRender()[i].GetAvgVertexDepth() < scene->GetTrianglesToRender()[j].GetAvgVertexDepth())
				{
					scene->SwapTriangleRenderOrder(i, j);
				}
			}
		}
	}
}

void Renderer::Render()
{
	/* ======================= NEEDS TO BE ABSTRACTED FROM HERE ===============================*/
	// Loop over projected triangle and render them
	//int num_triangles = array_length(triangles_to_render);
// 	for (int i = 0; i < num_triangles; i++)
// 	{
// 		triangle_t triangle = triangles_to_render[i];
// 
// 		if (render_vertices) display_vertices(triangle);
// 		if (render_faces) display_faces(triangle);
// 		if (render_wireframe) display_wireframe(triangle);
// 	}

	// Clear array of triangles every frame
	//array_free(triangles_to_render);
	RenderColorBuffer();
	ClearColorBuffer(SLATE_GRAY);
	SDL_RenderPresent(renderer);
}

void Renderer::Setup()
{
	colorBuffer.resize(GetWindowHeight() * GetWindowWidth());
	CreateRenderer();
	colorBufferTexture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, GetWindowWidth(), GetWindowHeight());
	//load_cube_mesh_data();
	//load_obj_file_data("./assets/cube.obj");
}
