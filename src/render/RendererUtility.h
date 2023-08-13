#pragma once
#include <iostream>
#include "SDL.h"
#include "vectors/VectorTypes.h"
#include "primatives/Triangle.h"

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

	void DisplayWireFrame(Triangle triangle);
	void DisplayFaces(Triangle triangle);
	void DisplayVertices(Triangle triangle);
	
	bool ShouldCullFace(const std::array<Vector4D, 3>& transformedVertices);
	Vector2D Project(Vector3D vec);
	Vector2D Project(Vector4D vec);
private:
	Renderer* owner;


};

