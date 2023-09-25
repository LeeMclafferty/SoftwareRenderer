#pragma once
#include <array>
#include <iostream>
#include "SDL.h"
#include "texture/Texture.h"
#include "vectors/VectorTypes.h"

class Triangle
{
public:
	Triangle();
	Triangle(std::array<Vector2D, 3> coords, int32_t color, float depth);
	Triangle(std::array<Vector2D, 3> coords, std::array<TextureCoord, 3> textCoordinates, Texture2D text, float depth);
	Triangle(std::array<Vector2D, 3> coords, Texture2D text, int32_t color, float depth);
	Triangle(std::array<Vector2D, 3> coords, std::array<TextureCoord, 3> textCoordinates, Texture2D text, int32_t color, float depth);
	
	std::array<Vector2D, 3> GetCoordinates() const { return coordinates; }
	const uint32_t GetFaceColor() const { return faceColor; }
	const float GetAvgVertexDepth() const { return avgVertexDepth; }
	Texture2D GetTexture() { return texture; }
	std::array<TextureCoord, 3> GetTextureCoordinates() const { return textureCoordinates; }

	void SetFaceColor(uint32_t color) { faceColor = color; }
	void SortVerticesAsc(Triangle& triangle);
	void SortVerticesAsc(Vector2D& vecA, Vector2D& vecB, Vector2D& vecC);
private:
	std::array<Vector2D, 3> coordinates;
	std::array<TextureCoord, 3> textureCoordinates;

	uint32_t faceColor;
	Texture2D texture;
	float avgVertexDepth;

};

