#pragma once
#include "Renderer.h"
enum class RenderState
{
	VerticesOnly,
	VerticesWireFrame,
	WireFrame,
	WireFrameFaces,
	FacesOnly,
	All
};

class RendererStateManager
{
public:
	friend Renderer;
	RendererStateManager();
	RendererStateManager(RenderState state);

private:
	const RenderState GetRenderState() const { return renderState; }
	void SetRenderState(RenderState newState) { renderState = newState; }
	RenderState renderState;
};

