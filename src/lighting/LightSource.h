#pragma once

#include "vectors/VectorTypes.h"
class LightSource
{
public: 
	LightSource();

	Vector3D GetLocation() const { return location; }
	float GetIntensity() const { return intensity; }
	uint32_t GetColor() const { return color; }

	void SetLocation(Vector3D updatedLocation) { location = updatedLocation; }
	void SetIntensity(float val) { intensity = val; }
	void SetColor(uint32_t newColor) { color = newColor; }

	virtual uint32_t ApplyLightingIntensity(uint32_t faceColor, float percentage) = 0;

private:
	Vector3D location;
	float intensity;
	uint32_t color;
};

