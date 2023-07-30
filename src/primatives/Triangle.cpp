#include "Triangle.h"
#include <iostream>
#include "core/Engine.h"
#include "vectors/VectorMath.h"
#include "colors/Colors.h"
#include "render/Renderer.h"
#include "render/RendererUtility.h"

Triangle::Triangle()
	:rendererUtility(Engine::GetInstance()->GetRenderer()->GetUtility()),
	coordinates{ Vector2D{100.f, 20.f}, Vector2D{200.f, 20.f}, Vector2D{150.f, 100.f} }, faceColor(WHITE)
{

}

Triangle::Triangle(std::array<Vector2D, 3> coords, int32_t color, float depth)
	:coordinates(coords), faceColor(color), avgVertexDepth(depth)
{

}

void Triangle::DrawTriangleWireFrame(const Vector2D& vecA, const Vector2D& vecB, const Vector2D& vecC, uint32_t color)
{
	if (!rendererUtility) return;

	rendererUtility->DrawLine(vecA.x, vecA.y, vecB.x, vecB.y, color);
	rendererUtility->DrawLine(vecA.y, vecB.y, vecC.x, vecC.y, color);
	rendererUtility->DrawLine(vecC.x, vecC.y, vecA.x, vecA.y, color);
}

void Triangle::DrawFilledTriangle(Vector2D& vecA, Vector2D& vecB, Vector2D& vecC, uint32_t color)
{
	SortVerticesAsc(vecA, vecB, vecC);

	/*
		Checks to see if the triangle is already flat top or bottom.
		This will prevent division by 0 as well.
	*/
	if (vecB.y == vecC.y)
	{
		FillFlatBottom(vecA, vecB, vecC, color);
	}
	else if (vecA.y == vecB.y)
	{
		FillFlatTop(vecA, vecB, vecC, color);
	}
	else
	{
		/* Calculate vertices midpoint for triangles being split */
		int my = vecB.y;
		int mx = (((vecC.x - vecA.x) * (vecB.y - vecA.y)) / (vecC.y - vecA.y)) + vecA.x;

		FillFlatTop(vecB, Vector2D(mx, my), vecC, color);
		FillFlatBottom(vecA, vecB, Vector2D(mx, my), color);
	}
}

/* Sorts Triangle vertices by y values */
void Triangle::SortVerticesAsc(Vector2D& vecA, Vector2D& vecB, Vector2D& vecC)
{
	if (vecA.y > vecB.y)
	{
		std::swap(vecA.y, vecB.y);
		std::swap(vecA.x, vecB.x);
	}
	if (vecB.y > vecC.y)
	{
		std::swap(vecB.y, vecC.y);
		std::swap(vecB.x, vecC.x);
	}
	if (vecA.y > vecB.y)
	{
		std::swap(vecA.y, vecB.y);
		std::swap(vecA.x, vecB.x);
	}
}

void Triangle::FillFlatTop(const Vector2D& vecA, const Vector2D& vecB, const Vector2D& vecC, uint32_t color)
{
	float slopeLeft = VectorMath::FindReciprocalSlope({ vecA.x, vecA.y }, { vecC.x, vecC.y });
	float slopeRight = VectorMath::FindReciprocalSlope({ vecB.x, vecB.y }, { vecC.x, vecC.y });

	float xStart = vecC.x;
	float xEnd = vecC.x;

	for (int y = vecC.y; y >= vecA.y; y--)
	{
		rendererUtility->DrawLine(xStart, y, xEnd, y, color);
		xStart -= slopeLeft;
		xEnd -= slopeRight;
	}
}

void Triangle::FillFlatBottom(const Vector2D& vecA, const Vector2D& vecB, const Vector2D& vecC, uint32_t color)
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
		rendererUtility->DrawLine(xStart, y, xEnd, y, color);
		xStart += inverseSlopeLeft;
		xEnd += inverseSlopeRight;
	}
}

