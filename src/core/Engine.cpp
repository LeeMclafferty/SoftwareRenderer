#include "Engine.h"
#include "Window.h"
#include "render/Renderer.h"
#include "InputHandler.h"

Engine::Engine(Renderer* mainRenderer, Scene* mainScene, Window* mainWindow)
	: bisRunning(false), window(mainWindow),
	renderer(mainRenderer), scene(mainScene),
	inputHandler(this) 
{
	CheckDependencies();
}


Engine::~Engine()
{
	SDL_Quit();
}

void Engine::Run()
{
	bisRunning = window->InitializeWindow();
	renderer->Setup();

	while (bisRunning)
	{
		inputHandler.ProcessInput();
		renderer->Update();
		renderer->Render();
	}
}

void Engine::CheckDependencies()
{
	if (renderer == nullptr)
	{
		throw std::invalid_argument("renderer must not be null");
	}
	else if (scene == nullptr)
	{
		throw std::invalid_argument("scene must not be null");
	}
	else if (window == nullptr)
	{
		throw std::invalid_argument("window must not be null");
	}
}

void Engine::SetupRenderer()
{

}

void Engine::SetupScene()
{

}
