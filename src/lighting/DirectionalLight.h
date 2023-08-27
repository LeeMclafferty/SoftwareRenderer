#pragma once
#include "LightSource.h"

class DirectionalLight : public LightSource
{

public:
	DirectionalLight();

	uint32_t ApplyLightingIntensity(uint32_t faceColor, float percentage);
};

