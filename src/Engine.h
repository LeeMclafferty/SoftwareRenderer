#pragma once
#include <iostream>
#include "SDL.h"
#include "Window.h"
#include "draw/Renderer.h"
#include "InputHandler.h"

/* Singleton Class*/
class Engine
{
public:
	static Engine* GetInstance();
	
	void Run();
	Window* GetWindow() { return &window; }
	const bool IsRunning() const { return bisRunning; }
	
	void SetIsRunning(bool newState) { bisRunning = newState; }

private:
	Engine();
	~Engine();
	static Engine* engineInstance;

	Window window;
	Renderer renderer;
	InputHandler inputHandler;

	bool bisRunning;
};

