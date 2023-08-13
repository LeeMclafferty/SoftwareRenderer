#pragma once

class Engine;

class InputHandler
{
public:
	InputHandler(Engine* renderEngine);
	void ProcessInput();

private:
	Engine* engine;

	void CheckDependencies();
};
