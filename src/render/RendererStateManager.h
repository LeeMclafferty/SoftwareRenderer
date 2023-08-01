#pragma once

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
	RendererStateManager();
	RendererStateManager(RenderState state);
	void SetRenderState(RenderState newState) { renderState = newState; }
	const RenderState GetRenderState() const { return renderState; }

private:
	RenderState renderState;
};

