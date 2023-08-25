#include "Camera.h"

Camera::Camera(int id, float as)
	:cameraLocation(Vector3D{0.f, 0.f, 0.f}), zoom(5.f), cameraId(id), fov(180/3), nearPlane(.1f), 
	farPlane(100.f), aspectRatio(as)
{

}

void Camera::IncreaseZoom(float amount)
{
	zoom += amount;
}

void Camera::DecreaseZoom(float amount)
{
	IncreaseZoom(-amount);
}
