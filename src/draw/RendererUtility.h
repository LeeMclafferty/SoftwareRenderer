#pragma once
#include <iostream>
#include "SDL.h"
#include "primatives/Triangle.h"

class Renderer;

class RendererUtility
{
public:
	friend class Renderer;
	RendererUtility();
	RendererUtility(Renderer* renderer);

private:
	std::unique_ptr<Renderer> owner;

	void DrawGrid(uint32_t color);
	void DrawPixel(int xPos, int yPos, uint32_t color);
	void DrawRectangle(int xPos, int yPos, int width, int height, uint32_t color);
	void DrawLine(int x0, int y0, int x1, int y1, uint32_t color);

	void DisplayWireFrame(Triangle triangle);
	void DisplayFaces(Triangle triangle);
	void DisplayVertices(Triangle triangle);
	//bool BackfaceCulling(const vec4_t* transformed_vertices);

};

