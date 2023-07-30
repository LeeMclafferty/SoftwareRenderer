#pragma once
#include <array>
#include "vectors/VectorTypes.h"

struct Matrix4x4
{
	std::array<std::array<float, 4>, 4> matrix;

	Vector4D operator*(const Vector4D& vec)
	{
		Vector4D result;
		result.x = matrix[0][0] * vec.x + matrix[0][1] * vec.y + matrix[0][2] * vec.z + matrix[0][3] * vec.w;
		result.y = matrix[1][0] * vec.x + matrix[1][1] * vec.y + matrix[1][2] * vec.z + matrix[1][3] * vec.w;
		result.z = matrix[2][0] * vec.x + matrix[2][1] * vec.y + matrix[2][2] * vec.z + matrix[2][3] * vec.w;
		result.w = matrix[3][0] * vec.x + matrix[3][1] * vec.y + matrix[3][2] * vec.z + matrix[3][3] * vec.w;
		return result;
	}
};

namespace MatrixMath
{
	Matrix4x4 GetIdentityMatrix()
	{
		Matrix4x4 mat = { {{
			{1, 0, 0, 0},
			{0, 1, 0, 0},
			{0, 0, 1, 0},
			{0, 0, 0, 1}
		}} };
		return mat;
	}

	Matrix4x4 MakeScaleMatrix(Vector3D scaleVec)
	{
		Matrix4x4 matrix = GetIdentityMatrix();
		matrix.matrix[0][0] = scaleVec.x;
		matrix.matrix[1][1] = scaleVec.y;
		matrix.matrix[2][2] = scaleVec.z;
		return matrix;
	}

	Matrix4x4 MakeTranslationMatrix(Vector3D transVec)
	{
		Matrix4x4 matrix = GetIdentityMatrix();
		matrix.matrix[0][3] = transVec.x;
		matrix.matrix[1][3] = transVec.y;
		matrix.matrix[2][3] = transVec.z;
		return matrix;
	}

	Matrix4x4 MakeRotationMatrix_Z(float angle)
	{
		float cosign = cos(angle);
		float sign = sin(angle);

		Matrix4x4 matrix = GetIdentityMatrix();
		matrix.matrix[0][0] = cosign;
		matrix.matrix[0][1] = -sign;
		matrix.matrix[1][0] = sign;
		matrix.matrix[1][1] = cosign;;
		return matrix;
	}

	Matrix4x4 MakeRotationMatrix_X(float angle)
	{
		float cosign = cos(angle);
		float sign = sin(angle);

		Matrix4x4 matrix = GetIdentityMatrix();
		matrix.matrix[1][1] = cosign;
		matrix.matrix[1][1] = -sign;
		matrix.matrix[2][1] = sign;
		matrix.matrix[2][2] = cosign;
		return matrix;
	}

	Matrix4x4 MakeRotationMatrix_Y(float angle)
	{
		float cosign = cos(angle);
		float sign = sin(angle);

		Matrix4x4 matrix = GetIdentityMatrix();
		matrix.matrix[0][0] = cosign;
		matrix.matrix[0][2] = sign;
		matrix.matrix[2][0] = -sign;
		matrix.matrix[2][2] = cosign;
		return matrix;
	}
}