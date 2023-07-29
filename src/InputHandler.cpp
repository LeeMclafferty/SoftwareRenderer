#include "InputHandler.h"
#include "Engine.h"

InputHandler::InputHandler()
{

}

void InputHandler::ProcessInput()
{
	SDL_Event event;
	SDL_PollEvent(&event);

	switch (event.type)
	{
	case SDL_QUIT:
		Engine::GetInstance()->SetIsRunning(false);
		break;
	case SDL_KEYDOWN:
		if (event.key.keysym.sym == SDLK_ESCAPE)
		{
			Engine::GetInstance()->SetIsRunning(false);
		}
// 		else if (event.key.keysym.sym == SDLK_1)
// 		{
// 			render_wireframe = render_wireframe ? false : true;
// 		}
// 		else if (event.key.keysym.sym == SDLK_2)
// 		{
// 			render_faces = render_faces ? false : true;
// 		}
// 		else if (event.key.keysym.sym == SDLK_3)
// 		{
// 			render_vertices = render_vertices ? false : true;
// 		}
// 		else if (event.key.keysym.sym == SDLK_c)
// 		{
// 			backface_culling_enabled = backface_culling_enabled ? false : true;
// 		}
// 		else if (event.key.keysym.sym == SDLK_i)
// 		{
// 			camera_zoom--;
// 		}
// 		else if (event.key.keysym.sym == SDLK_o)
// 		{
// 			camera_zoom++;
// 		}
// 		break;
	default:
		break;
	}
}
