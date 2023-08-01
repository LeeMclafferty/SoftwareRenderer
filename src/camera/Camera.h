#pragma once
#include "SDL.h"
#include "vectors/VectorTypes.h"

class Camera
{
public:
	Camera(int id);
	const Vector3D GetCameraLocation() const { return cameraLocation; }
	
	void IncreaseZoom(float amount);
	void DecreaseZoom(float amount);

	int GetId() const { return cameraId; }
private:
	/* Defaulted to scene origin */
	Vector3D cameraLocation;
	float fov;
	float zoom;
	int cameraId;
};

