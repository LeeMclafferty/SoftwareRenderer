#pragma once
#include <array>
#include "texture/Texture.h"
#include "vectors/VectorTypes.h"


class Face
{
public:
	Face();
	Face(std::array<int, 3> indexVerts, uint32_t faceColor);
	Face(std::array<int, 3> indexVerts, std::array<TextureCoord, 3> uvs, uint32_t faceColor);

	uint32_t GetColor() const { return color; }
	std::array<int, 3> GetIndices() const { return vertexIndices; }
	std::array<TextureCoord, 3> GetUvCoordinates() const { return uvCoordinates; }

	void SetColor(uint32_t faceColor) { color = faceColor; }
private:

	std::array<int, 3> vertexIndices;
	std::array<TextureCoord, 3> uvCoordinates;
	uint32_t color;

};

