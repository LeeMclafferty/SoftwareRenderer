#include <stdio.h>
#include <memory.h>
#include "Renderer.h"
#include "core/Engine.h"
#include "core/Scene.h"
#include "core/Window.h"
#include "colors/Colors.h"
#include "mesh/Mesh.h"
#include "matrix/Matrix.h"
#include "vectors/VectorMath.h"

Renderer::Renderer()
	:renderer(nullptr), fps(30), targetFrameTime(1000 / fps), colorBufferTexture(nullptr), utility(this),
	engine(nullptr)
{
}

Renderer::~Renderer()
{
	SDL_DestroyRenderer(renderer);
}

bool Renderer::CreateRenderer()
{
	if (!GetWindow()) return false;
	
	SDL_Window* window = GetWindow()->GetSdlWindow();
	renderer = SDL_CreateRenderer(GetWindow()->GetSdlWindow(), -1, 0);

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

int Renderer::GetWindowHeight()
{
	if (!GetWindow()) return 0;
	return 	GetWindow()->GetHeight();
}

int Renderer::GetWindowWidth()
{
	if (!GetWindow()) return 0;
	return 	GetWindow()->GetWidth();
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

void Renderer::SetEngine(Engine* renderEngine)
{
	engine = renderEngine;
}

Window* Renderer::GetWindow()
{
	if (!engine) return nullptr;
	return engine->GetWindow();
}

Scene* Renderer::GetScene()
{
	if (!engine) return nullptr;
	return engine->GetScene();
}

void Renderer::Update()
{
	if (!GetScene())
	{
		std::cout << "No scene found.\n";
		return;
	}

	SDL_Delay(targetFrameTime);


	/* I think later this can loop over all meshes in scene and render each. */
	if (!meshToRender)
	{
		meshToRender = std::make_shared<Mesh>();
	}

	meshToRender->SetRotation(Vector3D(meshToRender->GetRotation().x + .01, meshToRender->GetRotation().y + .01, meshToRender->GetRotation().z));
	Matrix4x4 scaleMatrix = MatrixMath::MakeScaleMatrix(meshToRender->GetScale());
	Matrix4x4 rotationMatrix_X = MatrixMath::MakeRotationMatrix_X(meshToRender->GetRotation().x);
	Matrix4x4 rotationMatrix_Y = MatrixMath::MakeRotationMatrix_Y(meshToRender->GetRotation().y);
	Matrix4x4 rotationMatrix_Z = MatrixMath::MakeRotationMatrix_Z(meshToRender->GetRotation().z);
	Matrix4x4 translationMatrix = MatrixMath::MakeTranslationMatrix(meshToRender->GetTranslation());

	for (int i = 0; i <= meshToRender->GetFaces().size() - 1; i++)
	{
		Face currentFace = meshToRender->GetFaces()[i];

		/* Subtract 1 to account for index in OBJ files*/
		std::array<Vector3D, 3> faceVertices;
		faceVertices[0] = meshToRender->GetVertices()[currentFace.GetIndices()[0] - 1];
		faceVertices[1] = meshToRender->GetVertices()[currentFace.GetIndices()[1] - 1];
		faceVertices[2] = meshToRender->GetVertices()[currentFace.GetIndices()[2] - 1];
		//currentFace.SetColor();

		/* Transform */
		std::array<Vector4D, 3> transformedVertices;
		for (int j = 0; j <= transformedVertices.size() - 1; j++)
		{
			Vector4D transformedVertex = VectorMath::Vector3ToVector4(faceVertices[j]);

			transformedVertex = scaleMatrix * transformedVertex;
			transformedVertex = rotationMatrix_X * transformedVertex;
			transformedVertex = rotationMatrix_Y * transformedVertex;
			transformedVertex = rotationMatrix_Z * transformedVertex;
			transformedVertex = translationMatrix * transformedVertex;

			// Translate vertex away from camera
			transformedVertex.z += GetScene()->GetViewportCamera()->GetZoom();
			transformedVertices[j] = transformedVertex;
		}

		bool shouldProject = true;
		if (backFaceCullingEnabled)
		{
			shouldProject = !utility.ShouldCullFace(transformedVertices);
		}

		/* Project */
		if (shouldProject)
		{
			std::array<Vector2D, 3> coordinatesToProject;
			for (int j = 0; j <= coordinatesToProject.size() - 1; j++)
			{
				// project current vertex
				coordinatesToProject[j] = utility.Project(VectorMath::Vector4ToVector3(transformedVertices[j]));

				/* Move to middle of screen */
				coordinatesToProject[j].x += (GetWindowWidth() / 2);
				coordinatesToProject[j].y += (GetWindowHeight() / 2);
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
			GetScene()->AddTriangleToRender(std::move(triangleToProject));
		}

	}
	/* Simple depth sort - painter's algorithm - Replace with z buffer*/
	for (int i = 0; i <= GetScene()->GetTrianglesToRender().size() - 1; i++)
	{
		for (int j = i + 1; j <= GetScene()->GetTrianglesToRender().size() - 1; j++)
		{
			if (GetScene()->GetTrianglesToRender()[i].GetAvgVertexDepth() < GetScene()->GetTrianglesToRender()[j].GetAvgVertexDepth())
			{
				GetScene()->SwapTriangleRenderOrder(i, j);
			}
		}
	}
}

void Renderer::Render()
{
	// Loop over projected triangle and render them
	for (int i = 0; i < GetScene()->GetTrianglesToRender().size(); i++)
	{
		Triangle triangle = GetScene()->GetTrianglesToRender()[i];
		utility.DisplayFaces(triangle);
		utility.DisplayVertices(triangle);
		utility.DisplayWireFrame(triangle);
// 		if (render_vertices) display_vertices(triangle);
// 		if (render_faces) display_faces(triangle);
// 		if (render_wireframe) display_wireframe(triangle);
	}

	GetScene()->EmptyTrianlgesToRender();
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
