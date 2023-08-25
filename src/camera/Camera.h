#pragma once
#include "SDL.h"
#include "vectors/VectorTypes.h"

class Camera
{
public:
	Camera(int id, float as);
	Vector3D GetCameraLocation() const { return cameraLocation; }
	
	float GetFov() const { return fov; }
	float GetNearPlane() const { return nearPlane; }
	float GetFarPlane() const { return farPlane; }
	float GetAspectRation() const { return aspectRatio; }

	float GetZoom() const { return zoom; }
	void IncreaseZoom(float amount);
	void DecreaseZoom(float amount);

	int GetId() const { return cameraId; }
private:
	/* Defaulted to scene origin */
	Vector3D cameraLocation;
	float zoom;
	int cameraId;
	
	float fov;
	float nearPlane;
	float farPlane;
	float aspectRatio;
};

