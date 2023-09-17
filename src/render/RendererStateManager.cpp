#include "RendererStateManager.h"

RendererStateManager::RendererStateManager()
	:renderState(RenderState::WireFrame)
{

}

RendererStateManager::RendererStateManager(RenderState state)
	:renderState(state)
{

}
