#pragma once
#include <array>
#include "vectors/VectorTypes.h"

class Face
{
public:
	Face();
	Face(std::array<int, 3> indexVerts, uint32_t faceColor);
	Face(std::array<int, 3> indexVerts, std::array<int, 3> indexTextures, std::array<int, 3> indexNormals, uint32_t faceColor);

	const uint32_t GetColor() const { return color; }
	const std::array<int, 3> GetIndices() const { return vertexIndices; }

	void SetColor(uint32_t faceColor) { color = faceColor; }
private:
	std::array<int, 3> vertexIndices;
	std::array<int, 3> textureIndices;
	std::array<int, 3> normalIndices;
	uint32_t color;
};

