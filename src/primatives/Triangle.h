#pragma once
#include <array>
#include <iostream>
#include "SDL.h"
#include "vectors/VectorTypes.h"

class RendererUtility;

class Triangle
{
public:
	Triangle();
	Triangle(std::array<Vector2D, 3> coords, int32_t color, float depth);
	/* Probably should rework all functions to take in 3 vector2D */
	void DrawTriangleWireFrame(const Vector2D& vecA, const Vector2D& vecB, const Vector2D& vecC, uint32_t color);
	void DrawFilledTriangle(Vector2D& vecA, Vector2D& vecB, Vector2D& vecC, uint32_t color);
	
	const std::array<Vector2D, 3> GetCoordinates() const { return coordinates; }
	const uint32_t GetFaceColor() const { return faceColor; }
	const float GetAvgVertexDepth() const { return avgVertexDepth; }

	void SetFaceColor(uint32_t color) { faceColor = color; }

private:
	std::shared_ptr<RendererUtility> rendererUtility;

	void SortVerticesAsc(Vector2D& vecA, Vector2D& vecB, Vector2D& vecC);
	void FillFlatTop(const Vector2D& vecA, const Vector2D& vecB, const Vector2D& vecC, uint32_t color);
	void FillFlatBottom(const Vector2D& vecA, const Vector2D& vecB, const Vector2D& vecC, uint32_t color);

	std::array<Vector2D, 3> coordinates;
	uint32_t faceColor;
	float avgVertexDepth;
};

