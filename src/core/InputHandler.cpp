#include <iostream>
#include "InputHandler.h"
#include "render/Renderer.h"
#include "render/RendererStateManager.h"

InputHandler::InputHandler()
	:engine(Engine::GetInstance())
{

}

void InputHandler::ProcessInput()
{
	if (!engine)
	{
		std::cout << "Could not process input, no engine found.\n";
		return;
	}

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
			engine->SetIsRunning(false);
		}
		else if (event.key.keysym.sym == SDLK_1)
		{
			engine->GetRenderer()->SetState(RenderState::FacesOnly);
		}
		else if (event.key.keysym.sym == SDLK_2)
		{
			engine->GetRenderer()->SetState(RenderState::WireFrame);
		}
		else if (event.key.keysym.sym == SDLK_3)
		{
			engine->GetRenderer()->SetState(RenderState::VerticesOnly);
		}
		else if (event.key.keysym.sym == SDLK_4)
		{
			engine->GetRenderer()->SetState(RenderState::VerticesWireFrame);
		}
		else if (event.key.keysym.sym == SDLK_5)
		{
			engine->GetRenderer()->SetState(RenderState::WireFrameFaces);
		}
		else if (event.key.keysym.sym == SDLK_6)
		{
			engine->GetRenderer()->SetState(RenderState::All);
		}
		else if (event.key.keysym.sym == SDLK_i)
		{
			Camera* camera = engine->GetScene()->GetViewportCamera();
			if (camera)
			{
				camera->IncreaseZoom(1.f);
			}
		}
		else if (event.key.keysym.sym == SDLK_o)
		{
			Camera* camera = engine->GetScene()->GetViewportCamera();
			if (camera)
			{
				camera->DecreaseZoom(1.f);
			}
		}
		break;
	default:
		break;
	}
}
