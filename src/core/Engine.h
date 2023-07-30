#pragma once

#include <iostream>
#include "SDL.h"

/* Singleton Class*/
class Engine
{
public:
	static Engine* GetInstance();
	
	void Run();
	
	class Window* GetWindow() { return &window; }
	class Renderer* GetRenderer()  { return &renderer; }
	class Scene* GetScene()  { return &scene; }

	bool IsRunning() const { return bisRunning; }
	void SetIsRunning(bool newState) { bisRunning = newState; }

private:
	Engine();
	~Engine();
	static Engine* engineInstance;

	class Window window;
	class Renderer renderer;
	class InputHandler inputHandler;
	class Scene scene;

	bool bisRunning;
};

