#include "Engine.h"
#include "Window.h"
#include "render/Renderer.h"
#include "InputHandler.h"

Engine::Engine()
	: bisRunning(false),
	window(std::make_shared<Window>()),
	renderer(std::make_shared<Renderer>()),
	inputHandler(std::make_shared<InputHandler>()),
	scene(std::make_shared<Scene>())
{
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
		inputHandler->ProcessInput();
		renderer->Update();
		renderer->Render();
	}
}
