#pragma once
#include "SDL.h"
#include "Engine.h"

class InputHandler
{
public:
	InputHandler();
	void ProcessInput();

private:
	Engine* engine;
};

