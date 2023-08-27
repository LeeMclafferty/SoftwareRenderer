#include "DirectionalLight.h"

DirectionalLight::DirectionalLight()
{

}

uint32_t DirectionalLight::ApplyLightingIntensity(uint32_t faceColor, float percentage)
{
	uint32_t alpha = faceColor & 0xFF000000;
	uint32_t red = (faceColor & 0x00FF0000) * percentage;
	uint32_t green = (faceColor & 0x0000FF00) * percentage;
	uint32_t blue = (faceColor & 0x000000FF) * percentage;

	uint32_t newColor = alpha | (faceColor & 0x00FF0000) | (faceColor & 0x0000FF00) | (faceColor & 0x000000FF);

	return newColor;
}
