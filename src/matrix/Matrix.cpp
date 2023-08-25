#include "Matrix.h"

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

	Matrix4x4 MakePerspectiveMatrix(float fov, float aspectRation, float zNear, float zFar)
	{
		Matrix4x4 mat;
		mat.matrix[0][0] = aspectRation * (1 / tan(fov / 2));
		mat.matrix[1][1] = 1 / tan(fov / 2);
		mat.matrix[2][2] = zFar / (zFar - zNear);
		mat.matrix[2][3] = (-zFar * zNear) / (zFar - zNear);
		mat.matrix[3][2] = 1.f;
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
}