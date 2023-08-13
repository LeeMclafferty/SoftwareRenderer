#include <iostream>
#include "InputHandler.h"
#include "render/RendererStateManager.h"
#include "render/Renderer.h"
#include "Engine.h"
#include "Scene.h"
#include "camera/Camera.h"

InputHandler::InputHandler(Engine* renderEngine)
	:engine(renderEngine)
{
	CheckDependencies();
}

void InputHandler::ProcessInput()
{
	Renderer* renderer = engine->GetRenderer();
	Scene* scene = engine->GetScene();
	Camera* camera = scene->GetViewportCamera();

	if (!engine || !renderer || !scene) return;

	SDL_Event event;
	SDL_PollEvent(&event);

	switch (event.type)
	{
	case SDL_QUIT:
		engine->SetIsRunning(false);
		break;
	case SDL_KEYDOWN:
		if (event.key.keysym.sym == SDLK_ESCAPE)
		{
			engine->SetIsRunning(false);
		}
		else if (event.key.keysym.sym == SDLK_1)
		{
			renderer->SetState(RenderState::FacesOnly);
		}
		else if (event.key.keysym.sym == SDLK_2)
		{
			renderer->SetState(RenderState::WireFrame);
		}
		else if (event.key.keysym.sym == SDLK_3)
		{
			renderer->SetState(RenderState::VerticesOnly);
		}
		else if (event.key.keysym.sym == SDLK_4)
		{
			renderer->SetState(RenderState::VerticesWireFrame);
		}
		else if (event.key.keysym.sym == SDLK_5)
		{
			renderer->SetState(RenderState::WireFrameFaces);
		}
		else if (event.key.keysym.sym == SDLK_6)
		{
			renderer->SetState(RenderState::All);
		}
		else if (event.key.keysym.sym == SDLK_i)
		{
			camera->IncreaseZoom(1.f);
		}
		else if (event.key.keysym.sym == SDLK_o)
		{
			camera->DecreaseZoom(1.f);
		}
			break;
		default:
			break;
	}
}

void InputHandler::CheckDependencies()
{
	if (engine == nullptr)
	{
		throw std::invalid_argument("Engine must not be null");
	}
}
