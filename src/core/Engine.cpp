#include "Engine.h"
#include "Window.h"
#include "render/Renderer.h"
#include "InputHandler.h"
#include "Scene.h"

Engine* Engine::engineInstance = nullptr;

Engine::Engine()
	:bisRunning(false)
{

}

Engine::~Engine()
{
	SDL_Quit();
}

Engine* Engine::GetInstance()
{
	if (!engineInstance)
	{
		engineInstance = new Engine();
	}
	else
	{
		return engineInstance;
	}

	return engineInstance;
}

void Engine::Run()
{
	bisRunning = window.InitializeWindow();
	renderer.Setup();
	
	while (bisRunning)
	{
		inputHandler.ProcessInput();
		renderer.Update();
		renderer.Render();
	}
}
