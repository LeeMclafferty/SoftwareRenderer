#pragma once
#include <array>
#include <iostream>
#include "SDL.h"
#include "vectors/VectorTypes.h"

class Triangle
{
public:
	Triangle();
	Triangle(std::array<Vector2D, 3> coords, int32_t color, float depth);
	
	std::array<Vector2D, 3> GetCoordinates() const { return coordinates; }
	const uint32_t GetFaceColor() const { return faceColor; }
	const float GetAvgVertexDepth() const { return avgVertexDepth; }

	void SetFaceColor(uint32_t color) { faceColor = color; }
	void SortVerticesAsc(Vector2D& vecA, Vector2D& vecB, Vector2D& vecC);

private:
	std::array<Vector2D, 3> coordinates;
	uint32_t faceColor;
	float avgVertexDepth;
};

