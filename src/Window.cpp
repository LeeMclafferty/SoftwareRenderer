#include "Window.h"

Window::Window()
	:window(nullptr), windowWidth(800), windowHeight(600)
{
}

Window::Window(int width, int height)
	:window(nullptr), windowWidth(width), windowHeight(height)
{
}

Window::~Window()
{
	DestroyWindow();
}

bool Window::InitializeWindow()
{
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		fprintf(stderr, "Error initializing SDL. \n");
		return false;
	}

	SDL_DisplayMode display_mode;
	SDL_GetCurrentDisplayMode(0, &display_mode);

	// Create SDL Window
	window = SDL_CreateWindow("CPU Renderer", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, windowWidth, windowHeight, SDL_WINDOW_RESIZABLE);
	if (!window)
	{
		fprintf(stderr, "Error Creating SDL Window. \n");
		return false;
	}

	return true;
}

void Window::DestroyWindow()
{
	SDL_DestroyWindow(window);
}
