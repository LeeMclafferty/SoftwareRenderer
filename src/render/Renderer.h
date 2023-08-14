#pragma once
#include <vector>
#include "SDL.h"
#include "RendererUtility.h"
#include "RendererStateManager.h"

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
};

