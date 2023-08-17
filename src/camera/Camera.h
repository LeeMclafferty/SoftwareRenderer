#pragma once
#include "SDL.h"
#include "vectors/VectorTypes.h"

class Camera
{
public:
	Camera(int id);
	Vector3D GetCameraLocation() const { return cameraLocation; }
	float GetFov() const { return fov; }

	float GetZoom() const { return zoom; }
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

