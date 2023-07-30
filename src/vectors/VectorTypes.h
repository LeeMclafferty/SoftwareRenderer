#pragma once
#include <iostream>

struct Vector2D
{
	float x;
	float y;

	Vector2D()
	{
		x = 0.f;
		y = 0.f;
	}

	Vector2D(float xVal, float yVal)
	{
		x = xVal;
		y = yVal;
	}

	Vector2D operator+(const Vector2D& otherVec) const
	{
		return { x + otherVec.x, y + otherVec.y };
	}

	Vector2D operator-(const Vector2D& otherVec) const 
	{
		return { x - otherVec.x, y - otherVec.y };
	}

	Vector2D operator*(const Vector2D& otherVec) const 
	{
		return { x * otherVec.x, y * otherVec.y };
	}

	Vector2D operator/(const Vector2D& otherVec) const
	{
		if (otherVec.x == 0 || otherVec.y == 0)
		{
			throw std::invalid_argument("Vector2D: Division by zero in vector division.");
		}
		return { x / otherVec.x, y / otherVec.y };
	}
};

struct Vector3D
{
	float x;
	float y;
	float z;

	Vector3D()
	{
		x = 0.f;
		y = 0.f;
		z = 0.f;
	}

	Vector3D(float xVal, float yVal, float zVal)
	{
		x = xVal;
		y = yVal;
		z = zVal;
	}

	Vector3D operator+(const Vector3D& otherVec) const
	{
		return { x + otherVec.x, y + otherVec.y, z + otherVec.z };
	}

	Vector3D operator-(const Vector3D& otherVec) const
	{
		return { x - otherVec.x, y - otherVec.y, z - otherVec.z };
	}

	Vector3D operator*(const Vector3D& otherVec) const
	{
		return { x * otherVec.x, y * otherVec.y, z * otherVec.z };
	}

	Vector3D operator/(const Vector3D& otherVec) const
	{
		if (otherVec.x == 0 || otherVec.y == 0 || otherVec.z == 0)
		{
			throw std::invalid_argument("Vector3D: Division by zero in vector division.");
		}
		return { x / otherVec.x, y / otherVec.y, z / otherVec.z };
	}
};

struct Vector4D
{
	float x;
	float y;
	float z;
	float w;
	
	Vector4D()
	{
		x = 0.f;
		y = 0.f;
		z = 0.f;
		w = 0.f;
	}

	Vector4D(float xVal, float yVal, float zVal, float wVal)
	{
		x = xVal;
		y = yVal;
		z = zVal;
		w = wVal;
	}
};