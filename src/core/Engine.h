#pragma once

#include <memory>
#include "SDL.h"

class Window;
class Renderer;
class InputHandler;
class Scene;

class Engine
{
public:
	Engine();
	~Engine();

	void Run();

	std::shared_ptr<Window> GetWindow() const { return window; }
	std::shared_ptr<Renderer> GetRenderer() const { return renderer; }
	std::shared_ptr<Scene> GetScene() const { return scene; }

	bool IsRunning() const { return bisRunning; }
	void SetIsRunning(bool newState) { bisRunning = newState; }

private:
	std::shared_ptr<Window> window;
	std::shared_ptr<Renderer> renderer;
	std::shared_ptr<InputHandler> inputHandler;
	std::shared_ptr<Scene> scene;

	bool bisRunning;
};
