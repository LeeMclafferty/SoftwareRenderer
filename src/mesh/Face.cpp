#include "Face.h"
#include "colors/Colors.h"
#include "lighting/LightSource.h"

Face::Face()
	:indices{ 0, 0, 0 }, color(WHITE)
{

}

Face::Face(std::array<int, 3> index, uint32_t faceColor)
	:indices(index), color(faceColor)
{

}
