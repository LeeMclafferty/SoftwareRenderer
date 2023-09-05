#include <iostream>
#include "SDL.h"
#include "core/Engine.h"
#include "core/Scene.h"
#include "render/Renderer.h"
#include "core/Window.h"

int main(int argc, char* args[])
{
    Window window;
    Renderer renderer;
    Scene scene(&window);
    Mesh ball(".\\assets\\ball.obj", "ball");
    scene.AddToMeshes(&ball);
    Engine engine(&renderer, &scene, &window);
    renderer.SetEngine(&engine);

    engine.Run();
    return 0;
}

