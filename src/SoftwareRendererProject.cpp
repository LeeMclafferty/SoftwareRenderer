#include <iostream>
#include "SDL.h"
#include "engine.h"

int main(int argc, char* args[])
{
    static Engine* renderEngine = Engine::GetInstance();
    renderEngine->Run();
    free(renderEngine);
    return 0;
}

