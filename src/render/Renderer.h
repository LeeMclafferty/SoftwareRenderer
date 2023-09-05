#pragma once
#include <vector>
#include "SDL.h"
#include "RendererUtility.h"
#include "RendererStateManager.h"
#include "matrix/Matrix.h"

class Scene;
class Mesh;

class Renderer
{
public:
	Renderer();
	~Renderer();

	SDL_Renderer* GetSdlRenderer() { return renderer; }
	RendererUtility* GetUtility() { return &utility; }
	void Update();
	void Render();
	void Setup();

	int GetWindowHeight();
	int GetWindowWidth();

	void AddToColorBuffer(int index, uint32_t color);

	RenderState GetRenderState() const { return stateManager.GetRenderState(); }
	void SetState(RenderState state) { stateManager.SetRenderState(state); }

	void SetEngine(class Engine* renderEngine);

	class Window* GetWindow();
	class Scene* GetScene();

	/* TEMP */
	bool backFaceCullingEnabled = true;
private:
	SDL_Renderer* renderer;
	bool CreateRenderer();

	RendererUtility utility;
	RendererStateManager stateManager;

	int fps;
	int targetFrameTime;

	SDL_Texture* colorBufferTexture;
	std::vector<uint32_t> colorBuffer;
	void ClearColorBuffer(uint32_t color);
	void RenderColorBuffer();

	class Engine* engine;
	std::shared_ptr<Mesh> meshToRender;

	Matrix4x4 projectionMatrix;

	void UpdateMeshToRender();
	void ProjectTriangles();
	Matrix4x4 BuildTransformationMatrix() const;
	Vector4D TransformVertex(const Vector3D& vertex, const Matrix4x4& transformationMatrix);
	bool ShouldCullFace(const std::array<Vector4D, 3>& transformedVertices);
	Vector4D ProjectVertex(const Vector4D& vertex);
};

