#pragma once

#include "vectors/VectorTypes.h"
class LightSource
{
public: 
	LightSource();

	Vector3D GetDirection() const { return direction; }
	float GetIntensity() const { return intensity; }
	uint32_t GetColor() const { return color; }

	void SetDirection(Vector3D updatedDirection) { direction = updatedDirection; }
	void SetIntensity(float val) { intensity = val; }
	void SetColor(uint32_t newColor) { color = newColor; }

	virtual uint32_t ApplyLightingIntensity(uint32_t faceColor, float percentage) = 0;

private:
	Vector3D direction;
	float intensity;
	uint32_t color;
};

