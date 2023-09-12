#pragma once
#include <stdint.h>
#include <vector>

class Texture2D
{

public:
	Texture2D();
	Texture2D(float uCoord, float vCoord);

	float GetUCoordinate() const { return u; }
	float GetVCoordinate() const { return v; }
	int GetWidth() const { return width; }
	int GetHeight() const { return height; }

	std::vector<uint32_t> GetTexture() const { return texture; }
	std::vector<uint8_t> GetRedBrickTexture() const { return redBrick_T; }

private:
	float u;
	float v;
	int width;
	int height;

	std::vector<uint32_t> texture;
	std::vector<uint8_t> redBrick_T;
};

