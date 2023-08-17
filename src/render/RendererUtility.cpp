#include "colors/Colors.h"
#include "render/RendererUtility.h"
#include "render/Renderer.h"
#include "vectors/VectorMath.h"
#include "core/Scene.h"
#include "core/Engine.h"

RendererUtility::RendererUtility(Renderer* renderer)
 :owner(renderer)
{

}

RendererUtility::RendererUtility()
 :owner(nullptr)
{

}

void RendererUtility::DrawGrid(uint32_t color)
{
	if (!owner) return;

	for (int y = 0; y < owner->GetWindowHeight(); y += 10) //rows
	{
		for (int x = 0; x < owner->GetWindowWidth(); x += 10) //columns
		{
			owner->AddToColorBuffer((owner->GetWindowWidth() * y) + x, color);
		}
	}
}

void RendererUtility::DrawFilledRectangle(int xPos, int yPos, int width, int height, uint32_t color)
{
	for (int i = 0; i < height; i++) // rows
	{
		for (int j = 0; j < width; j++) // columns
		{
			/* Use the passed in position as an offset to draw rectangle. */
			int x = xPos + j;
			int y = yPos + i;
			DrawPixel(x, y, color);
		}
	}
}

void RendererUtility::DrawPixel(int xPos, int yPos, uint32_t color)
{
	if (!owner) return;
	if (xPos >= 0 && yPos >= 0 && xPos < owner->GetWindowWidth() && yPos < owner->GetWindowHeight())
	{
		owner->AddToColorBuffer((owner->GetWindowWidth() * yPos) + xPos, color);
	}
}

void RendererUtility::DrawLine(int x0, int y0, int x1, int y1, uint32_t color)
{
	int changeX = x1 - x0;
	int changeY = y1 - y0;

	int longestSide = (abs(changeX) >= abs(changeY)) ? abs(changeX) : abs(changeY);

	float xIncrement = changeX / (float)longestSide;
	float yIncrement = changeY / (float)longestSide;

	float currentX = (float)x0;
	float currentY = (float)y0;

	/* increment and draw pixel until line has traveled as far as the longest side. */
	for (int i = 0; i <= longestSide; i++)
	{
		DrawPixel((int)round(currentX), (int)round(currentY), color);
		currentX += (float)xIncrement;
		currentY += (float)yIncrement;
	}
}

void RendererUtility::DisplayWireFrame(const Triangle& triangle)
{
	DrawTriangleWireFrame(
		Vector2D(triangle.GetCoordinates()[0].x, triangle.GetCoordinates()[0].y),
		Vector2D(triangle.GetCoordinates()[1].x, triangle.GetCoordinates()[1].y),
		Vector2D(triangle.GetCoordinates()[2].x, triangle.GetCoordinates()[2].y),
		BLACK
	);
}

void RendererUtility::DisplayFaces(Triangle& triangle)
{
	Vector2D v1(triangle.GetCoordinates()[0].x, triangle.GetCoordinates()[0].y);
	Vector2D v2(triangle.GetCoordinates()[1].x, triangle.GetCoordinates()[1].y);
	Vector2D v3(triangle.GetCoordinates()[2].x, triangle.GetCoordinates()[2].y);
	DrawFilledTriangle(triangle, triangle.GetFaceColor() );
}

/* Draw Rectangle instead of pixel just so the vertices look bigger */
void RendererUtility::DisplayVertices(const Triangle& triangle)
{
	DrawFilledRectangle(triangle.GetCoordinates()[0].x, triangle.GetCoordinates()[0].y, 3, 3, LIME_GREEN);
	DrawFilledRectangle(triangle.GetCoordinates()[1].x, triangle.GetCoordinates()[1].y, 3, 3, LIME_GREEN);
	DrawFilledRectangle(triangle.GetCoordinates()[2].x, triangle.GetCoordinates()[2].y, 3, 3, LIME_GREEN);
}

bool RendererUtility::ShouldCullFace(const std::array<Vector4D, 3>& transformedVertices)
{
	if (!owner) return false;
	
	Camera* camera = owner->GetScene()->GetViewportCamera();

	if (!camera) return false;

	Vector3D vec_a = VectorMath::Vector4ToVector3(transformedVertices[0]);
	Vector3D vec_b = VectorMath::Vector4ToVector3(transformedVertices[2]);
	Vector3D vec_c = VectorMath::Vector4ToVector3(transformedVertices[1]);

	Vector3D vec_ab = vec_b - vec_a;
	Vector3D vec_ac = vec_c - vec_a;
	VectorMath::Normalize(vec_ab);
	VectorMath::Normalize(vec_ac);

	Vector3D normal = VectorMath::CrossProduct(vec_ab, vec_ac);
	VectorMath::Normalize(normal);
	Vector3D camera_ray = camera->GetCameraLocation() - vec_a;

	// if dot is negative, the face is not seen by the camera, so skip projection
	if (VectorMath::DotProduct(normal, camera_ray) < 0)
	{
		return false;
	}

	return true;
}

Vector2D RendererUtility::Project(const Vector3D& vec)
{
	Camera* camera = owner->GetScene()->GetViewportCamera();

	if (!camera) return Vector2D(0.f, 0.f);
	
	if (vec.z == 0)
	{
		return Vector2D(0.f, 0.f);
	}

	return Vector2D((camera->GetFov() * vec.x) / vec.z, (camera->GetFov() * vec.y) / vec.z);
}

void RendererUtility::DrawTriangleWireFrame(const Vector2D& vecA, const Vector2D& vecB, const Vector2D& vecC, uint32_t color)
{
	DrawLine(vecA.x, vecA.y, vecB.x, vecB.y, color);
	DrawLine(vecB.x, vecB.y, vecC.x, vecC.y, color);
	DrawLine(vecC.x, vecC.y, vecA.x, vecA.y, color);
}

void RendererUtility::DrawFilledTriangle(Triangle& triangle, uint32_t color)
{
	Vector2D& vecA = triangle.GetCoordinates()[0];
	Vector2D& vecB = triangle.GetCoordinates()[1];
	Vector2D& vecC = triangle.GetCoordinates()[2];

	triangle.SortVerticesAsc(vecA, vecB, vecC);

	/*
		Checks to see if the triangle is already flat top or bottom.
		This will prevent division by 0 as well.
	*/
	if (vecB.y == vecC.y)
	{
		FillFlatBottomTriangle(vecA, vecB, vecC, color);
	}
	else if (vecA.y == vecB.y)
	{
		FillFlatTopTriangle(vecA, vecB, vecC, color);
	}
	else
	{
		/* Calculate vertices midpoint for triangles being split */
		int my = vecB.y;
		int mx = (((vecC.x - vecA.x) * (vecB.y - vecA.y)) / (vecC.y - vecA.y)) + vecA.x;

		FillFlatTopTriangle(vecB, Vector2D(mx, my), vecC, color);
		FillFlatBottomTriangle(vecA, vecB, Vector2D(mx, my), color);
	}
}

void RendererUtility::FillFlatTopTriangle(const Vector2D& vecA, const Vector2D& vecB, const Vector2D& vecC, uint32_t color)
{
	float slopeLeft = VectorMath::FindReciprocalSlope({ vecA.x, vecA.y }, { vecC.x, vecC.y });
	float slopeRight = VectorMath::FindReciprocalSlope({ vecB.x, vecB.y }, { vecC.x, vecC.y });

	float xStart = vecC.x;
	float xEnd = vecC.x;

	for (int y = vecC.y; y >= vecA.y; y--)
	{
		DrawLine(xStart, y, xEnd, y, color);
		xStart -= slopeLeft;
		xEnd -= slopeRight;
	}
}

void RendererUtility::FillFlatBottomTriangle(const Vector2D& vecA, const Vector2D& vecB, const Vector2D& vecC, uint32_t color)
{
	/*
	Passed coordinates in the "incorrect" order to get the inverse slope value.
	We inverse them since y increases going down in screen space.
	*/
	float inverseSlopeLeft = VectorMath::FindReciprocalSlope({ vecA.x, vecA.y }, { vecB.x, vecB.y });
	float inverseSlopeRight = VectorMath::FindReciprocalSlope({ vecC.x, vecC.y }, { vecA.x, vecA.y });

	float xStart = vecA.x;
	float xEnd = vecA.x;

	for (int y = vecA.y; y <= vecC.y; y++)
	{
		DrawLine(xStart, y, xEnd, y, color);
		xStart += inverseSlopeLeft;
		xEnd += inverseSlopeRight;
	}
}
