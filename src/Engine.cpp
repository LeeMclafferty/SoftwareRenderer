#include "Engine.h"


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
