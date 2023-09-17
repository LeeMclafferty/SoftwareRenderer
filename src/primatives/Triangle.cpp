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

Triangle::Triangle(std::array<Vector2D, 3> coords, int32_t color, float depth)
	:coordinates(coords), faceColor(color), avgVertexDepth(depth)
{

}

Triangle::Triangle(std::array<Vector2D, 3> coords, std::array<TextureCoord, 3> textCoordinates, Texture2D text, float depth)
	:coordinates(coords), textureCoordinates(textCoordinates), texture(text), avgVertexDepth(depth)
{

}

Triangle::Triangle(std::array<Vector2D, 3> coords, std::array<TextureCoord, 3> textCoordinates, Texture2D text, int32_t color, float depth)
	:coordinates(coords), textureCoordinates(textCoordinates), texture(text), faceColor(color), avgVertexDepth(depth)
{

}

Triangle::Triangle(std::array<Vector2D, 3> coords, Texture2D text, int32_t color, float depth)
	:coordinates(coords), texture(text), faceColor(color), avgVertexDepth(depth)
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

void Triangle::SortVerticesAsc(Triangle& triangle)
{
	 
	 Vector2D& vecA = triangle.coordinates[0];
	 Vector2D& vecB = triangle.coordinates[1];
	 Vector2D& vecC = triangle.coordinates[2];
	 
	 TextureCoord& texA = triangle.textureCoordinates[0];
	 TextureCoord& texB = triangle.textureCoordinates[1];
	 TextureCoord& texC = triangle.textureCoordinates[2];
	 
	 if (vecA.y > vecB.y)
	 {
	 	std::swap(vecA, vecB);
	 	std::swap(texA, texB);
	 }
	 if (vecB.y > vecC.y)
	 {
	 	std::swap(vecB, vecC);
	 	std::swap(texB, texC);
	 }
	 if (vecA.y > vecB.y)
	 {
		 std::swap(vecA, vecB);
		 std::swap(texA, texB);
	 }
}

