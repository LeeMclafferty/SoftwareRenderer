#pragma once
#include "SDL.h"
#include <stdio.h>

class Window
{
public:
	Window();
	Window(int width, int height);
	~Window();

	SDL_Window* GetSdlWindow() { return window; }
	bool InitializeWindow();

	const int GetWidth() const { return windowWidth;  }
	const int GetHeight() const { return windowHeight; }
private:
	SDL_Window* window;
	int windowWidth;
	int windowHeight;
	void DestroyWindow();
};

