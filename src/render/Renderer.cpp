#include <stdio.h>
#include <memory.h>
#include "Renderer.h"
#include "core/Engine.h"
#include "core/Scene.h"
#include "core/Window.h"
#include "colors/Colors.h"
#include "mesh/Mesh.h"
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
// 		std::string fileName = ".\\assets\\f22.obj";
// 		std::string meshName = "Plane";
// 		meshToRender = std::make_shared<Mesh>(fileName, meshName);
		meshToRender = std::make_shared<Mesh>();
	}

	meshToRender->SetRotation(Vector3D(meshToRender->GetRotation().x + .01, 
		meshToRender->GetRotation().y + .01, meshToRender->GetRotation().z + .01
	));
// 	meshToRender->SetScale(Vector3D(meshToRender->GetScale().x + .005, 
// 		meshToRender->GetScale().y + .005, meshToRender->GetScale().z + .005
// 	));
// 	meshToRender->SetLocation(Vector3D( meshToRender->GetLocation().x + .02,
// 		meshToRender->GetLocation().y + .02, meshToRender->GetLocation().z + .02
// 	));

	Matrix4x4 scaleMatrix = MatrixMath::MakeScaleMatrix(meshToRender->GetScale());
	Matrix4x4 rotationMatrix_X = MatrixMath::MakeRotationMatrix_X(meshToRender->GetRotation().x);
	Matrix4x4 rotationMatrix_Y = MatrixMath::MakeRotationMatrix_Y(meshToRender->GetRotation().y);
	Matrix4x4 rotationMatrix_Z = MatrixMath::MakeRotationMatrix_Z(meshToRender->GetRotation().z);
	Matrix4x4 translationMatrix = MatrixMath::MakeTranslationMatrix(meshToRender->GetLocation());

	for (int i = 0; i <= meshToRender->GetFaces().size() - 1; i++)
	{
		Face currentFace = meshToRender->GetFaces()[i];

		/* Subtract 1 to account for index in OBJ files*/
		std::array<Vector3D, 3> faceVertices;
		faceVertices[0] = meshToRender->GetVertices()[currentFace.GetIndices()[0] - 1];
		faceVertices[1] = meshToRender->GetVertices()[currentFace.GetIndices()[1] - 1];
		faceVertices[2] = meshToRender->GetVertices()[currentFace.GetIndices()[2] - 1];
		//currentFace.SetColor(WHITE);

		/* Transform */
		std::array<Vector4D, 3> transformedVertices;
		for (int j = 0; j <= transformedVertices.size() - 1; j++)
		{
			Vector4D transformedVertex = VectorMath::Vector3ToVector4(faceVertices[j]);

			Matrix4x4 sceneMatrix = MatrixMath::GetIdentityMatrix();
			sceneMatrix = (scaleMatrix * sceneMatrix);
			sceneMatrix = (rotationMatrix_X* sceneMatrix);
			sceneMatrix = (rotationMatrix_Y * sceneMatrix);
			sceneMatrix = (rotationMatrix_Z * sceneMatrix);
			sceneMatrix = (translationMatrix * sceneMatrix);

			transformedVertex = sceneMatrix * transformedVertex;

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
			std::array<Vector4D, 3> coordinatesToProject;
			for (int j = 0; j <= coordinatesToProject.size() - 1; j++)
			{
				// project current vertex
				coordinatesToProject[j] = MatrixMath::PerspectiveDivide(projectionMatrix, transformedVertices[j]);

				/* Scale and Move to middle of screen */
				coordinatesToProject[j].x = (coordinatesToProject[j].x) * 0.5 * GetWindowWidth();
				coordinatesToProject[j].y = (coordinatesToProject[j].y) * 0.5 * GetWindowHeight();

				coordinatesToProject[j].x += (GetWindowWidth() / 2.f);
				coordinatesToProject[j].y += (GetWindowHeight() / 2.f);
			}

			/* Replace with a z buffer */
			float faceDepth = (transformedVertices[0].z + transformedVertices[1].z + transformedVertices[2].z) / 3.0;

			Triangle triangleToProject (
				std::array<Vector2D, 3> {
					Vector2D(coordinatesToProject[0].x, coordinatesToProject[0].y),
					Vector2D(coordinatesToProject[1].x, coordinatesToProject[1].y),
					Vector2D(coordinatesToProject[2].x, coordinatesToProject[2].y)
				},
				currentFace.GetColor(),
				faceDepth
			);
			GetScene()->AddTriangleToRender(std::move(triangleToProject));
		}

	}

	std::cout << "Tri's to render: " << GetScene()->GetTrianglesToRender().size() << std::endl;
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
		utility.RenderByState(triangle);
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

	if (GetScene())
	{
		const Camera* cam = GetScene()->GetViewportCamera();
		projectionMatrix = MatrixMath::MakePerspectiveMatrix(cam->GetFov(), cam->GetAspectRation(), cam->GetNearPlane(), cam->GetFarPlane());
	}
}
