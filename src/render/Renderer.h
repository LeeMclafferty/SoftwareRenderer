#pragma once
#include <vector>
#include "SDL.h"
#include "RendererUtility.h"
#include "camera/Camera.h"
#include "core/Scene.h"
#include "RendererStateManager.h"

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

	const int GetWindowHeight() const;
	const int GetWindowWidth() const;

	void AddToColorBuffer(int index, uint32_t color);

	const RenderState GetRenderState() const { return stateManager.GetRenderState(); }
	void SetState(RenderState state) { stateManager.SetRenderState(state); }
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

	Scene* scene;

};

