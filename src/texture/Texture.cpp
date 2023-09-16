#include "Texture.h"

TextureCoord::TextureCoord()
	:width(64), height(64)
{

}

TextureCoord::TextureCoord(float uCoord, float vCoord)
	:width(64), height(64), u(uCoord), v(vCoord)
{
	
}

