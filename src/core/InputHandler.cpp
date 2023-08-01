#include <iostream>
#include "InputHandler.h"
#include "render/RendererStateManager.h"
#include "render/Renderer.h"
#include "Engine.h"
#include "Scene.h"
#include "camera/Camera.h"

InputHandler::InputHandler()
	:engine(std::make_shared<Engine>(Engine::GetInstance()))
{

}

void InputHandler::ProcessInput()
{
	std::shared_ptr<Engine> spEngine = engine.lock();
	std::shared_ptr<Renderer> spRenderer = spEngine->GetRenderer().lock();
	std::shared_ptr<Scene> spScene = spEngine->GetScene().lock();
	std::shared_ptr<Camera> spCamera = spScene->GetViewportCamera().lock();

	if (!spEngine || !spRenderer || !spScene) return;

	SDL_Event event;
	SDL_PollEvent(&event);

	switch (event.type)
	{
	case SDL_QUIT:
		spEngine->SetIsRunning(false);
		break;
	case SDL_KEYDOWN:
		if (event.key.keysym.sym == SDLK_ESCAPE)
		{
			spEngine->SetIsRunning(false);
		}
		else if (event.key.keysym.sym == SDLK_1)
		{
			spRenderer->SetState(RenderState::FacesOnly);
		}
		else if (event.key.keysym.sym == SDLK_2)
		{
			spRenderer->SetState(RenderState::WireFrame);
		}
		else if (event.key.keysym.sym == SDLK_3)
		{
			spRenderer->SetState(RenderState::VerticesOnly);
		}
		else if (event.key.keysym.sym == SDLK_4)
		{
			spRenderer->SetState(RenderState::VerticesWireFrame);
		}
		else if (event.key.keysym.sym == SDLK_5)
		{
			spRenderer->SetState(RenderState::WireFrameFaces);
		}
		else if (event.key.keysym.sym == SDLK_6)
		{
			spRenderer->SetState(RenderState::All);
		}
		else if (event.key.keysym.sym == SDLK_i)
		{
			if (spCamera)
			{
				spCamera->IncreaseZoom(1.f);
			}
		}
		else if (event.key.keysym.sym == SDLK_o)
		{
			if (spCamera)
			{
				spCamera->DecreaseZoom(1.f);
			}
		}
			break;
		default:
			break;
	}
}
