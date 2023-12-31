#pragma once
#include <iostream>
#include <vector>
#include "SDL.h"
#include "vectors/VectorTypes.h"
#include "primatives/Triangle.h"
#include "RendererStateManager.h"

class Renderer;

class RendererUtility
{
public:

	RendererUtility();
	RendererUtility(Renderer* renderer);

	void DrawGrid(uint32_t color);
	void DrawPixel(int xPos, int yPos, uint32_t color);
	void DrawLine(int x0, int y0, int x1, int y1, uint32_t color);
	void DrawFilledRectangle(int xPos, int yPos, int width, int height, uint32_t color);

	void DisplayWireFrame(const Triangle& triangle);
	void DisplayFaces(Triangle& triangle);
	void DisplayVertices(const Triangle& triangle);
	void DisplayTexturedTriangle(Triangle& triangle);
	
	bool ShouldCullFace(const std::array<Vector4D, 3>& transformedVertices);
	Vector2D Project(const Vector3D& vec);

	void DrawTriangleWireFrame(const Vector2D& vecA, const Vector2D& vecB, const Vector2D& vecC, uint32_t color);
	void DrawFilledTriangle(Triangle& triangle, uint32_t color);
	void DrawTexturedTriangle(Triangle& triangle);
	void FillFlatTopTriangle(const Vector2D& vecA, const Vector2D& vecB, const Vector2D& vecC, uint32_t color);
	void FillFlatBottomTriangle(const Vector2D& vecA, const Vector2D& vecB, const Vector2D& vecC, uint32_t color);

	void FillFlatTopTriangle(Triangle& tri, const Vector2D& vecC);
	void FillFlatBottomTriangle(Triangle& tri, const Vector2D& vecC);
	
	void RenderByState(Triangle& triangle);
private:
	Renderer* owner;

	bool ShouldRenderFaces();
	bool ShouldRenderVertices();
	bool ShouldRenderWireframe();
	bool ShouldRenderTexture();
	bool CheckForMatchingState(const Renderer* renderer, const std::vector<RenderState>& statesToCheck);
	void DrawTexel(float x, float y, Triangle& tri);


	Vector3D BarycentricWeights(const Triangle& tri, const Vector2D& point);
};

