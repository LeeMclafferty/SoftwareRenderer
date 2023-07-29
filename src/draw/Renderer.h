#pragma once
#include <vector>
#include "SDL.h"
#include "RendererUtility.h"

class Renderer
{
public:
	Renderer();
	~Renderer();

	const SDL_Renderer* GetSdlRenderer() const { return renderer; }
	void Update();
	void Render();
	void Setup();

	const int GetWindowHeight() const;
	const int GetWindowWidth() const;

	void AddToColorBuffer(int index, uint32_t color);

private:
	SDL_Renderer* renderer;
	bool CreateRenderer();

	RendererUtility utility;

	int fps;
	int targetFrameTime;

	SDL_Texture* colorBufferTexture;
	std::vector<uint32_t> colorBuffer;
	void ClearColorBuffer(uint32_t color);
	void RenderColorBuffer();


};

