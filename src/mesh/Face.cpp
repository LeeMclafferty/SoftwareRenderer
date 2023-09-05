#include "Face.h"
#include "colors/Colors.h"
#include "lighting/LightSource.h"

Face::Face()
	:vertexIndices{ 0, 0, 0 }, textureIndices{ 0, 0, 0 }, normalIndices{ 0, 0 ,0 }, color(WHITE)
{

}

Face::Face(std::array<int, 3> indexVerts, std::array<int, 3> indexTextures, std::array<int, 3> indexNormals, uint32_t faceColor)
	:vertexIndices(indexVerts), textureIndices(indexTextures), normalIndices(indexNormals), color(faceColor)
{

}

Face::Face(std::array<int, 3> indexVerts, uint32_t faceColor)
	:vertexIndices(indexVerts), textureIndices{ 0, 0, 0 }, normalIndices{ 0, 0 ,0 }, color(WHITE)
{

}
