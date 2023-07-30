#include "RendererStateManager.h"

RendererStateManager::RendererStateManager()
	:renderState(RenderState::All)
{

}

RendererStateManager::RendererStateManager(RenderState state)
	:renderState(state)
{

}
