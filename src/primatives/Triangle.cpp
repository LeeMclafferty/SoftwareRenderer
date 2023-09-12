#include "Triangle.h"
#include <iostream>
#include "core/Engine.h"
#include "vectors/VectorMath.h"
#include "colors/Colors.h"
#include "render/Renderer.h"
#include "render/RendererUtility.h"

Triangle::Triangle()
	:coordinates({{Vector2D(100.f, 20.f), Vector2D(200.f, 20.f), Vector2D(150.f, 100.f)}}), faceColor(WHITE),
	avgVertexDepth(0.f)
{

}

Triangle::Triangle(std::array<Vector2D, 3> coords, std::array<Texture2D, 3> textCoordinates, int32_t color, float depth)
	:coordinates(coords), textureCoordinates(textCoordinates), faceColor(color), avgVertexDepth(depth)
{

}

/* Sorts Triangle vertices by y values */
void Triangle::SortVerticesAsc(Vector2D& vecA, Vector2D& vecB, Vector2D& vecC)
{
	if (vecA.y > vecB.y)
	{
		std::swap(vecA.y, vecB.y);
		std::swap(vecA.x, vecB.x);
	}
	if (vecB.y > vecC.y)
	{
		std::swap(vecB.y, vecC.y);
		std::swap(vecB.x, vecC.x);
	}
	if (vecA.y > vecB.y)
	{
		std::swap(vecA.y, vecB.y);
		std::swap(vecA.x, vecB.x);
	}
}
