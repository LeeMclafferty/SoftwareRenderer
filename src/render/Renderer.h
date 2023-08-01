#pragma once
#include <vector>
#include "SDL.h"
#include "RendererUtility.h"
#include "RendererStateManager.h"

class Scene;

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

	int GetWindowHeight() const;
	int GetWindowWidth() const;

	void AddToColorBuffer(int index, uint32_t color);

	const RenderState GetRenderState() const { return stateManager->GetRenderState(); }
	void SetState(RenderState state) { stateManager->SetRenderState(state); }

	/* TEMP */
	bool backFaceCullingEnabled = true;
private:
	SDL_Renderer* renderer;
	bool CreateRenderer();

	RendererUtility utility;
	std::shared_ptr<RendererStateManager> stateManager;
	std::weak_ptr<Scene> scene;

	int fps;
	int targetFrameTime;

	SDL_Texture* colorBufferTexture;
	std::vector<uint32_t> colorBuffer;
	void ClearColorBuffer(uint32_t color);
	void RenderColorBuffer();


};

