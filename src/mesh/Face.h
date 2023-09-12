#pragma once
#include <array>
#include "texture/Texture2D.h"
#include "vectors/VectorTypes.h"

class Face
{
public:
	Face();
	Face(std::array<int, 3> indexVerts, uint32_t faceColor);
	Face(std::array<int, 3> indexVerts, std::array<Texture2D, 3> uvs, uint32_t faceColor);

	uint32_t GetColor() const { return color; }
	std::array<int, 3> GetIndices() const { return vertexIndices; }
	std::array<Texture2D, 3> GetUvCoordinates() const { return uvCoordinates; }

	void SetColor(uint32_t faceColor) { color = faceColor; }
private:

	std::array<int, 3> vertexIndices;
	std::array<Texture2D, 3> uvCoordinates;
	uint32_t color;

};

