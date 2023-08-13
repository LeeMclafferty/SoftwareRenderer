#include "vectors/VectorMath.h"


Vector3D VectorMath::PitchRotation(const Vector3D& v, float angle)
{
	Vector3D rotatedVector = {
		v.x,
		v.y * (float)cos(angle) - v.z * (float)sin(angle),
		v.y * (float)sin(angle) + v.z * (float)cos(angle)
	};

	return rotatedVector;
}

Vector3D VectorMath::YawRotation(const Vector3D& v, float angle)
{
	Vector3D rotatedVector = {
		v.x * (float)cos(angle) - v.z * (float)sin(angle),
		v.y,
		v.x * (float)sin(angle) + v.z * (float)cos(angle)
	};

	return rotatedVector;
}

Vector3D VectorMath::RollRotation(const Vector3D& v, float angle)
{
	Vector3D rotatedVector = {
		v.x * (float)cos(angle) - v.y * (float)sin(angle),
		v.x * (float)sin(angle) + v.y * (float)cos(angle),
		v.z
	};

	return rotatedVector;
}

float VectorMath::Length(const Vector2D& v)
{
	return (float)(sqrt(pow(v.x, 2) + pow(v.y, 2)));
}

Vector3D VectorMath::CrossProduct(const Vector3D& a, const Vector3D& b)
{
	float x = a.y * b.z - a.z * b.y;
	float y = a.z * b.x - a.x * b.z;
	float z = a.x * b.y - a.y * b.x;
	Vector3D cross = { x, y, z };
	return cross;
}

float VectorMath::DotProduct(const Vector3D& a, const Vector3D& b)
{
	float result = (a.x * b.x) + (a.y * b.y) + (a.z * b.z);
	return result;
}

void VectorMath::Normalize(Vector2D& v)
{
	float len = Length(v);
	v.x /= len;
	v.y /= len;
}

Vector3D VectorMath::Vector4ToVetor3(const Vector4D v)
{
	Vector3D result = { v.x, v.y, v.z };
	return result;
}

Vector4D VectorMath::Vector3ToVector4(const Vector3D& v)
{
	Vector4D result = { v.x, v.y, v.z, 1.f };
	return result;
}

float VectorMath::FindReciprocalSlope(const Vector2D& coordA, const Vector2D& coordB)
{
	float changeX = coordB.x - coordA.x;
	float changeY = coordB.y - coordA.y;

	if (changeY == 0.0f)
	{
		throw std::invalid_argument("Slope is undefined for vertical line.");
	}
	return changeX / changeY;
}

void VectorMath::Normalize(Vector3D& v)
{
	float len = Length(v);
	v.x /= len;
	v.y /= len;
	v.z /= len;
}

float VectorMath::Length(const Vector3D& v)
{
	return (float)(sqrt(pow(v.x, 2) + pow(v.y, 2) + pow(v.z, 2)));
}
