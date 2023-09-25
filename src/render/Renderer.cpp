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

	UpdateMeshToRender();
	ProjectTriangles();

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

void Renderer::UpdateMeshToRender()
{
	if (!GetScene())
	{
		std::cout << "No scene found.\n";
		return;
	}

	SDL_Delay(targetFrameTime);
	
	/* I want to add the functionality to loop over all meshes stored in scene and render them. I might need to move assigning the mesh to render to a UpdateScene function later. */
	if (!meshToRender)
	{
		//meshToRender = std::shared_ptr<Mesh>(GetScene()->GetMesh("ball"));
		meshToRender = std::make_shared<Mesh>();
	}

	meshToRender->SetRotation(Vector3D(
		meshToRender->GetRotation().x + .00,
		meshToRender->GetRotation().y + .00,
		meshToRender->GetRotation().z + .00
	));
}

void Renderer::ProjectTriangles()
{
	const auto& faces = meshToRender->GetFaces();
	const auto& vertices = meshToRender->GetVertices();
	Matrix4x4 transformationMatrix = BuildTransformationMatrix();

	for (size_t i = 0; i < faces.size(); i++) 
	{
		Face currentFace = meshToRender->GetFaces()[i];

		/* Subtract 1 to account for index in OBJ files*/
		std::array<Vector3D, 3> faceVertices = {
			vertices[currentFace.GetIndices()[0] - 1],
			vertices[currentFace.GetIndices()[1] - 1],
			vertices[currentFace.GetIndices()[2] - 1]
		};
		currentFace.SetColor(RED);

		/* Transform */
		std::array<Vector4D, 3> transformedVertices;
		for (int j = 0; j < 3; ++j) 
		{
			transformedVertices[j] = TransformVertex(faceVertices[j], transformationMatrix);
		}

		if (ShouldCullFace(transformedVertices))
		{
			std::array<Vector4D, 3> projectedVertices;
			for (int j = 0; j < 3; ++j)
			{
				projectedVertices[j] = ProjectVertex(transformedVertices[j]);
			}

			/* Need to implement z-buffer to have pixel depth per pixel before I can do smooth shading */
			uint32_t color = GetScene()->GetSun()->ApplyFlatLighting(currentFace.GetColor(), VectorMath::DotProduct(VectorMath::GetNormal(transformedVertices), GetScene()->GetSun()->GetDirection()));

			float faceDepth = (transformedVertices[0].z + transformedVertices[1].z + transformedVertices[2].z) / 3.0;

			Triangle triangleToProject(
				std::array<Vector2D, 3> {
					Vector2D(projectedVertices[0].x, projectedVertices[0].y),
					Vector2D(projectedVertices[1].x, projectedVertices[1].y),
					Vector2D(projectedVertices[2].x, projectedVertices[2].y)
				},
				color,
				faceDepth
			);
			GetScene()->AddTriangleToRender(std::move(triangleToProject));
		}
	}
}

Matrix4x4 Renderer::BuildTransformationMatrix() const 
{
	Matrix4x4 scaleMatrix = MatrixMath::MakeScaleMatrix(meshToRender->GetScale());
	Matrix4x4 rotationMatrix_X = MatrixMath::MakeRotationMatrix_X(meshToRender->GetRotation().x);
	Matrix4x4 rotationMatrix_Y = MatrixMath::MakeRotationMatrix_Y(meshToRender->GetRotation().y);
	Matrix4x4 rotationMatrix_Z = MatrixMath::MakeRotationMatrix_Z(meshToRender->GetRotation().z);
	Matrix4x4 translationMatrix = MatrixMath::MakeTranslationMatrix(meshToRender->GetLocation());

	Matrix4x4 sceneMatrix = MatrixMath::GetIdentityMatrix();
	sceneMatrix = scaleMatrix * sceneMatrix;
	sceneMatrix = rotationMatrix_X * sceneMatrix;
	sceneMatrix = rotationMatrix_Y * sceneMatrix;
	sceneMatrix = rotationMatrix_Z * sceneMatrix;
	sceneMatrix = translationMatrix * sceneMatrix;

	return sceneMatrix;
}

Vector4D Renderer::TransformVertex(const Vector3D& vertex, const Matrix4x4& transformationMatrix) 
{
	Vector4D transformedVertex = VectorMath::Vector3ToVector4(vertex);
	transformedVertex = transformationMatrix * transformedVertex;
	transformedVertex.z += GetScene()->GetViewportCamera()->GetZoom();
	return transformedVertex;
}

bool Renderer::ShouldCullFace(const std::array<Vector4D, 3>& transformedVertices) 
{
	if (backFaceCullingEnabled) 
	{
		return !utility.ShouldCullFace(transformedVertices);
	}
	return true;
}

Vector4D Renderer::ProjectVertex(const Vector4D& vertex) 
{
	Vector4D projected = MatrixMath::PerspectiveDivide(projectionMatrix, vertex);
	projected.y *= -1; // Inverse y to be projected right side-up.
	projected.x = (projected.x) * 0.5 * GetWindowWidth() + (GetWindowWidth() / 2.f);
	projected.y = (projected.y) * 0.5 * GetWindowHeight() + (GetWindowHeight() / 2.f);
	return projected;
}