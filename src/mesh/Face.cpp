#include "Face.h"
#include "colors/Colors.h"
#include "lighting/LightSource.h"

Face::Face()
	:vertexIndices{ 0, 0, 0 }, color(WHITE)
{

}

Face::Face(std::array<int, 3> indexVerts, uint32_t faceColor)
	:vertexIndices(indexVerts), color(faceColor)
{

}

Face::Face(std::array<int, 3> indexVerts, std::array<Texture2D, 3> uvs, uint32_t faceColor)
	:vertexIndices(indexVerts), uvCoordinates(uvs), color(WHITE)
{

} 