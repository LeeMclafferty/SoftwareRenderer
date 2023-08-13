#pragma once
#include "VectorTypes.h"
#include "math.h"

/* Vector arithmetic can be found in VectorTypes.h as overloaded operators */
namespace VectorMath 
{
	/*
	*	Pitch	- Rotate around x
	*	Yaw		- Rotate around y
	*	Roll	- Rotate around z
	*/
	Vector3D PitchRotation(const Vector3D& v, float angle);

	Vector3D YawRotation(const Vector3D& v, float angle);

	Vector3D RollRotation(const Vector3D& v, float angle);

	/* Length function use Pythagorean theorem */
	float Length(const Vector2D& v);

	float Length(const Vector3D& v);

	/* Linear Algebra */
	Vector3D CrossProduct(const Vector3D& a, const Vector3D& b);

	float DotProduct(const Vector3D& a, const Vector3D& b);

	void Normalize(Vector2D& v);

	void Normalize(Vector3D& v);

	Vector3D Vector4ToVetor3(const Vector4D v);

	Vector4D Vector3ToVector4(const Vector3D& v);

	/* 
		Normally slope is rise over run, but since we are incrementing y then moving over for our
		scan line functions, this function has to return run over rise.
	*/
	float FindReciprocalSlope(const Vector2D& coordA, const Vector2D& coordB);
}
