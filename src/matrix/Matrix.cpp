#include "Matrix.h"
#include <math.h>
#include <SDL_stdinc.h>

namespace MatrixMath
{
	Matrix4x4 GetIdentityMatrix()
	{
		Matrix4x4 mat;
		mat.matrix = { {
			{1, 0, 0, 0},
			{0, 1, 0, 0},
			{0, 0, 1, 0},
			{0, 0, 0, 1}
		} };
		return mat;
	}

	Matrix4x4 MakeScaleMatrix(const Vector3D& scaleVec)
	{
		Matrix4x4 matrix = GetIdentityMatrix();
		matrix.matrix[0][0] = scaleVec.x;
		matrix.matrix[1][1] = scaleVec.y;
		matrix.matrix[2][2] = scaleVec.z;
		return matrix;
	}

	Matrix4x4 MakeTranslationMatrix(const Vector3D& transVec)
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
		matrix.matrix[1][2] = -sign;
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

	Matrix4x4 MakePerspectiveMatrix(float fov, float aspectRatio, float zNear, float zFar)
	{
		float radiansFOV = fov * (M_PI / 180.0);
		Matrix4x4 mat;
		mat.matrix[0][0] = aspectRatio * (1 / tan(radiansFOV / 2));
		mat.matrix[1][1] = 1 / tan(radiansFOV / 2);
		mat.matrix[2][2] = zFar / (zFar - zNear);
		mat.matrix[2][3] = (-zFar * zNear) / (zFar - zNear);
		mat.matrix[3][2] = -1.f;
		return mat;
	}

	Vector4D PerspectiveDivide(Matrix4x4 project, Vector4D vec)
	{
		Vector4D result = project * vec;

		if (result.w != 0.f)
		{
			result.x /= result.w;
			result.y /= result.w;
			result.z /= result.w;
		}
		return result;
	}

	Matrix4x4 ZeroMatrix()
	{
		Matrix4x4 mat; // Initialized to a zero matrix, so just return it.  
		return mat;
	}
}