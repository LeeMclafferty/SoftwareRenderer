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

	Matrix4x4 operator*(const Matrix4x4& mat)
	{
		Matrix4x4 result;

		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				result.matrix[i][j] = (matrix[i][0] * mat.matrix[0][j]) + 
					(matrix[i][1] * mat.matrix[1][j]) + 
					(matrix[i][2] * mat.matrix[2][j]) + 
					(matrix[i][3] * mat.matrix[3][j]);
			}
		}

		return result;
	}
};

namespace MatrixMath
{
	Matrix4x4 GetIdentityMatrix();
	Matrix4x4 MakeScaleMatrix(const Vector3D& scaleVec);
	Matrix4x4 MakeTranslationMatrix(const Vector3D& transVec);
	Matrix4x4 MakeRotationMatrix_Z(float angle);
	Matrix4x4 MakeRotationMatrix_X(float angle);
	Matrix4x4 MakeRotationMatrix_Y(float angle);
	Matrix4x4 MakePerspectiveMatrix(float fov, float aspectRation, float zNear, float zFar);
	Vector4D PerspectiveDivide(Matrix4x4 project, Vector4D vec);
}