#pragma once

class Engine;

class InputHandler
{
public:
	InputHandler();
	void ProcessInput();

private:
	std::weak_ptr<Engine> engine;
};

