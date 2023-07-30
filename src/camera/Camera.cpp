#include "Camera.h"

Camera::Camera(int id)
	:cameraLocation(Vector3D{0.f, 0.f, 0.f}), fov(640), zoom(5.f), cameraId(id)
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
