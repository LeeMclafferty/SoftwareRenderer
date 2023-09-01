#pragma once
#include <array>
#include "vectors/VectorTypes.h"

class Face
{
public:
	Face();
	Face(std::array<int, 3> index, uint32_t faceColor);

	const uint32_t GetColor() const { return color; }
	const std::array<int, 3> GetIndices() const { return indices; }

	void SetColor(uint32_t faceColor) { color = faceColor; }
private:
	std::array<int, 3> indices;
	uint32_t color;
};

