#pragma once

#include "SDL.h"
#include "InputHandler.h"

class Renderer;
class Scene;
class Window;

class Engine
{
public:
	Engine(Renderer* renderer, Scene* mainScene, Window* mainWindow);
	~Engine();

	void Run();

	Window* GetWindow() const { return window; }
	Renderer* GetRenderer() const { return renderer; }
	Scene* GetScene() const { return scene; }

	bool IsRunning() const { return bisRunning; }
	void SetIsRunning(bool newState) { bisRunning = newState; }

private:
	Renderer* renderer;
	Scene* scene;
	Window* window;

	InputHandler inputHandler;

	bool bisRunning;

	void CheckDependencies();
	void SetupRenderer();
	void SetupScene();
};
