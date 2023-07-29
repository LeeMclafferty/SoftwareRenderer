#pragma once
#include <iostream>
#include "SDL.h"

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

// 	void display_wireframe(triangle_t triangle);
// 	void display_faces(triangle_t triangle);
// 	void display_vertices(triangle_t triangle);
// 	bool backface_culling(const vec4_t* transformed_vertices);

};

