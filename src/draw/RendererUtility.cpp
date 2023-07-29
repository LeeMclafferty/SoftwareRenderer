#include "RendererUtility.h"
#include "Renderer.h"

RendererUtility::RendererUtility()
	:owner(nullptr)
{

}

RendererUtility::RendererUtility(Renderer* renderer)
	:owner(renderer)
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

void RendererUtility::DrawRectangle(int xPos, int yPos, int width, int height, uint32_t color)
{
	for (int i = 0; i < height; i++) // rows
	{
		for (int j = 0; j < width; j++) // columns
		{
			/* Use the passed in position as an offset to draw rectangle. */
			int x = xPos + i;
			int y = yPos + j;
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

void RendererUtility::DisplayWireFrame(Triangle triangle)
{

}

void RendererUtility::DisplayFaces(Triangle triangle)
{

}

void RendererUtility::DisplayVertices(Triangle triangle)
{

}

// bool RendererUtility::BackfaceCulling(const vec4_t* transformed_vertices)
// {
// 
// }
