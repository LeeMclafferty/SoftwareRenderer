#include <iostream>
#include "SDL.h"
#include "core/Engine.h"

int main(int argc, char* args[])
{
    static Engine* renderEngine = Engine::GetInstance();
    renderEngine->Run();
    free(renderEngine);
    return 0;
}

