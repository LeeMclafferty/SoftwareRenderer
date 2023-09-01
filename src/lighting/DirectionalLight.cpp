#include "DirectionalLight.h"

DirectionalLight::DirectionalLight()
{

}

uint32_t DirectionalLight::ApplyLightingIntensity(uint32_t faceColor, float percentage)
{
	uint32_t alpha = faceColor & 0xFF000000;

	uint32_t red = ((faceColor & 0x00FF0000) >> 16) * percentage;
	uint32_t green = ((faceColor & 0x0000FF00) >> 8) * percentage;
	uint32_t blue = (faceColor & 0x000000FF) * percentage;

	// Clamp values to ensure they remain in the 0-255 range
	red = (red > 255) ? 255 : red;
	green = (green > 255) ? 255 : green;
	blue = (blue > 255) ? 255 : blue;

	uint32_t newColor = alpha | (red << 16) | (green << 8) | blue;
	return newColor;
}

