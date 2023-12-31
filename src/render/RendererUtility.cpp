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
	DrawFilledTriangle(triangle, triangle.GetFaceColor());
}

/* Draw Rectangle instead of pixel just so the vertices look bigger */
void RendererUtility::DisplayVertices(const Triangle& triangle)
{
	DrawFilledRectangle(triangle.GetCoordinates()[0].x, triangle.GetCoordinates()[0].y, 4, 4, LIME_GREEN);
	DrawFilledRectangle(triangle.GetCoordinates()[1].x, triangle.GetCoordinates()[1].y, 4, 4, LIME_GREEN);
	DrawFilledRectangle(triangle.GetCoordinates()[2].x, triangle.GetCoordinates()[2].y, 4, 4, LIME_GREEN);
}

void RendererUtility::DisplayTexturedTriangle(Triangle& triangle)
{
	DrawTexturedTriangle(triangle);
}

bool RendererUtility::ShouldCullFace(const std::array<Vector4D, 3>& transformedVertices)
{
	if (!owner) return false;
	
	Camera* camera = owner->GetScene()->GetViewportCamera();

	if (!camera) return false;

	Vector3D vec_a = VectorMath::Vector4ToVector3(transformedVertices[0]);
	Vector3D normal = VectorMath::GetNormal(transformedVertices);
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
	Vector2D vecA = triangle.GetCoordinates()[0];
	Vector2D vecB = triangle.GetCoordinates()[1];
	Vector2D vecC = triangle.GetCoordinates()[2];

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

void RendererUtility::DrawTexturedTriangle(Triangle& triangle)
{
	triangle.SortVerticesAsc(triangle);

	Vector2D& vecA = triangle.GetCoordinates()[0];
	Vector2D& vecB = triangle.GetCoordinates()[1];
	Vector2D& vecC = triangle.GetCoordinates()[2];

	if (vecB.y == vecC.y)
	{
		FillFlatBottomTriangle(triangle, vecC);
	}
	else if (vecA.y == vecB.y)
	{
		FillFlatTopTriangle(triangle, vecC);
	}
	else
	{
		int my = vecB.y;
		int mx = (((vecC.x - vecA.x) * (vecB.y - vecA.y)) / (vecC.y - vecA.y)) + vecA.x;

		FillFlatTopTriangle(triangle, Vector2D(mx, my));
		FillFlatBottomTriangle(triangle, Vector2D(mx, my));
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

void RendererUtility::FillFlatTopTriangle(Triangle& tri, const Vector2D& vecC)
{
	Vector2D& vecA = tri.GetCoordinates()[0];
	Vector2D& vecB = tri.GetCoordinates()[1];

	float inverseSlopeLeft = VectorMath::FindReciprocalSlope({ vecC.x, vecC.y }, { vecB.x, vecB.y });
	float inverseSlopeRight = VectorMath::FindReciprocalSlope({ vecC.x, vecC.y }, { vecA.x, vecA.y });

	for (int y = vecB.y; y <= vecC.y; y++)
	{
		int xStart = vecB.x + (y - vecB.y) * inverseSlopeLeft;
		int xEnd = vecA.x + (y - vecA.y) * inverseSlopeRight;

		if (vecC.y - vecB.y == 0) continue;

		if (xEnd < xStart)
		{
			std::swap(xStart, xEnd);
		}
		for (int x = xStart; x < xEnd; x++)
		{
			//DrawPixel(x, y, CORAL);
			DrawTexel(x, y, tri);
		}
	}
}

/* For drawing colors with no textures */
void RendererUtility::FillFlatBottomTriangle(const Vector2D& vecA, const Vector2D& vecB, const Vector2D& vecC, uint32_t color)
{
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

void RendererUtility::FillFlatBottomTriangle(Triangle& tri, const Vector2D& vecC)
{

	Vector2D& vecA = tri.GetCoordinates()[0];
	Vector2D& vecB = tri.GetCoordinates()[1];

	float inverseSlopeLeft = VectorMath::FindReciprocalSlope({ vecA.x, vecA.y }, { vecB.x, vecB.y });
	float inverseSlopeRight = VectorMath::FindReciprocalSlope({ vecC.x, vecC.y }, { vecA.x, vecA.y });

	for (int y = vecA.y; y <= vecB.y; y++)
	{
		int xStart = vecB.x + (y - vecB.y) * inverseSlopeLeft;
		int xEnd = vecA.x + (y - vecA.y) * inverseSlopeRight;

		if(vecB.y - vecA.y == 0) continue;

		if (xEnd < xStart)
		{
			std::swap(xStart, xEnd);
		}
		for (int x = xStart; x < xEnd; x++)
		{
			//DrawPixel(x, y, CYAN);
			DrawTexel(x, y, tri);
		}
	}
}

void RendererUtility::RenderByState(Triangle& triangle)
{
	if (ShouldRenderFaces())
	{
		DisplayFaces(triangle);
	}
	
	if (ShouldRenderVertices())
	{
		DisplayVertices(triangle);
	}
	
	if (ShouldRenderWireframe())
	{
		DisplayWireFrame(triangle);
	}

	if (ShouldRenderTexture())
	{
		DisplayTexturedTriangle(triangle);
	}
}

bool RendererUtility::ShouldRenderFaces()
{
	if (!owner) return false;

	std::vector<RenderState> compatibleStates {
		RenderState::FacesOnly, RenderState::WireFrameFaces
	};

	return CheckForMatchingState(owner, compatibleStates);
}

bool RendererUtility::ShouldRenderVertices()
{
	if (!owner) return false;

	std::vector<RenderState> compatibleStates {
		RenderState::VerticesOnly, RenderState::VerticesWireFrame
	};

	return CheckForMatchingState(owner, compatibleStates);
}

bool RendererUtility::ShouldRenderWireframe()
{
	if (!owner) return false;

	std::vector<RenderState> compatibleStates {
		RenderState::WireFrame, RenderState::WireFrameFaces, RenderState::VerticesWireFrame, RenderState::All
	};

	return CheckForMatchingState(owner, compatibleStates);
}

bool RendererUtility::ShouldRenderTexture()
{
	if (!owner) return false;

	std::vector<RenderState> compatibleStates {
		RenderState::Textured, RenderState::TexturedWireFrame, RenderState::All
	};

	return CheckForMatchingState(owner, compatibleStates);
}

bool RendererUtility::CheckForMatchingState(const Renderer* renderer, const std::vector<RenderState>& statesToCheck)
{
	if (!renderer) return false;

	RenderState state = owner->GetRenderState();

	for (auto compState : statesToCheck)
	{
		if (compState == state)
		{
			return true;
		}
	}

	return false;
}

// Drawing pixel not working, too tiered to look into it now.
void RendererUtility::DrawTexel(float x, float y, Triangle& tri)
{
	Vector2D point = { x, y };
	Vector3D weights = BarycentricWeights(tri, point);

	float alpha = weights.x;
	float beta = weights.y;
	float gamma = weights.z;

	float u0 = tri.GetTextureCoordinates()[0].GetUCoordinate();
	float u1 = tri.GetTextureCoordinates()[1].GetUCoordinate();
	float u2 = tri.GetTextureCoordinates()[2].GetUCoordinate();

	float v0 = tri.GetTextureCoordinates()[0].GetVCoordinate();
	float v1 = tri.GetTextureCoordinates()[1].GetVCoordinate();
	float v2 = tri.GetTextureCoordinates()[2].GetVCoordinate();

	float interpU = (u0 * alpha) + (u1 * beta) + (u2 * gamma);
	float interpV = (v0 * alpha) + (v1 * beta) + (v2 * gamma);

	int textureX = interpU * tri.GetTexture().GetWidth();
	int textureY = interpV * tri.GetTexture().GetHeight();

	int pixelLocation = (tri.GetTexture().GetWidth() * textureY) + textureX;
	if (pixelLocation < tri.GetTexture().GetTexture().size())
	{
		DrawPixel(x, y, tri.GetTexture().GetTexture()[pixelLocation]);
	}
}

Vector3D RendererUtility::BarycentricWeights(const Triangle& tri, const Vector2D& point)
{
	Vector2D& vecA = tri.GetCoordinates()[0];
	Vector2D& vecB = tri.GetCoordinates()[1];
	Vector2D& vecC = tri.GetCoordinates()[2];

	Vector2D ac = vecC - vecA;
	Vector2D ab = vecB - vecA;
	Vector2D ap = point - vecA;
	Vector2D pc = vecC - point;
	Vector2D pb = vecB - point;

	float areaParallelogramAbc = (ac.x * ab.y - ac.y * ab.x);

	if (fabs(areaParallelogramAbc) < 1e-5)
		return Vector3D(0, 0, 0);

	float alpha = (pc.x * pb.y - pc.y * pb.x) / areaParallelogramAbc;
	float beta = (ac.x * ap.y - ac.y * ap.x) / areaParallelogramAbc;
	float gamma = 1 - alpha - beta;

	return Vector3D(alpha, beta, gamma);
}
