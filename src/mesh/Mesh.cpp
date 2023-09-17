#include "Mesh.h"
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <array>
#include <colors/Colors.h>

/* Default Constructor constructs cube mesh */
Mesh::Mesh()
	:rotation(Vector3D{0.f, 0.f, 0.f}), scale(Vector3D{1.f, 1.f, 1.f}), translation(Vector3D{0.f, 0.f, 0.f}), name("Default Cube")
{
	vertices = {
		{ -1, -1, -1 }, // 1
		{ -1,  1, -1 }, // 2
		{  1,  1, -1 }, // 3
		{  1, -1, -1 }, // 4
		{  1,  1,  1 }, // 5
		{  1, -1,  1 }, // 6
		{ -1,  1,  1 }, // 7
		{ -1, -1,  1 }  // 8
	};

	faces = {
		// front
		{ {1, 2, 3}, {TextureCoord(0, 0), TextureCoord(0, 1), TextureCoord(0, 1)}, CORAL},
		{ {1, 3, 4}, {TextureCoord(0, 0), TextureCoord(1, 1), TextureCoord(1, 0)}, CORAL },
		// right
		{ {4, 3, 5}, {TextureCoord(0, 0), TextureCoord(0, 1), TextureCoord(0, 1)}, SEA_GREEN },
		{ {4, 5, 6}, {TextureCoord(0, 0), TextureCoord(1, 1), TextureCoord(1, 0)}, SEA_GREEN },
		// back
		{ {6, 5, 7}, {TextureCoord(0, 0), TextureCoord(0, 1), TextureCoord(0, 1)}, SKY_BLUE },
		{ {6, 7, 8}, {TextureCoord(0, 0), TextureCoord(1, 1), TextureCoord(1, 0)}, SKY_BLUE},
		// left
		{ {8, 7, 2}, {TextureCoord(0, 0), TextureCoord(0, 1), TextureCoord(0, 1)}, GOLD },
		{ {8, 2, 1}, {TextureCoord(0, 0), TextureCoord(1, 1), TextureCoord(1, 0)}, GOLD},
		// top
		{ {2, 7, 5}, {TextureCoord(0, 0), TextureCoord(0, 1), TextureCoord(0, 1)}, MEDIUM_PURPLE },
		{ {2, 5, 3}, {TextureCoord(0, 0), TextureCoord(1, 1), TextureCoord(1, 0)}, MEDIUM_PURPLE },
		// bottom
		{ {6, 8, 1}, {TextureCoord(0, 0), TextureCoord(0, 1), TextureCoord(0, 1)}, DEEP_PINK },
		{ {6, 1, 4}, {TextureCoord(0, 0), TextureCoord(1, 1), TextureCoord(1, 0)}, DEEP_PINK }
	};

	texture = Texture2D();
}

Mesh::Mesh(std::string file, std::string meshName)
	:rotation(Vector3D{ 0.f, 0.f, 0.f }), scale(Vector3D{ 1.f, 1.f, 1.f }), translation(Vector3D{ 0.f, 0.f, 0.f }), name(meshName)
{
	LoadObjData(file);
}

void Mesh::LoadObjData(const std::string& fileName)
{
	FILE* file;
	fopen_s(&file, fileName.c_str(), "r");
	char line[1024];

	while (fgets(line, 1024, file)) 
	{
		PushVerticies(line);
		PushFaces(line);
	}
}

void Mesh::PushVerticies(char* line)
{
	if (strncmp(line, "v ", 2) == 0)
	{
		Vector3D vertex;
		sscanf_s(line, "v %f %f %f", &vertex.x, &vertex.y, &vertex.z);
		vertices.push_back(vertex);
	}
}

void Mesh::PushFaces(char* line)
{
	if (strncmp(line, "f ", 2) == 0)
	{
		std::array<int, 3> vertexIndices;
		std::array<int, 3> textureIndices;
		std::array<int, 3> normalIndices;

		// Initialize arrays to avoid undefined behavior
		memset(&vertexIndices, 0, sizeof(vertexIndices));
		memset(&textureIndices, 0, sizeof(textureIndices));
		memset(&normalIndices, 0, sizeof(normalIndices));

		int matched = sscanf_s(
			line, "f %d/%d/%d %d/%d/%d %d/%d/%d",
			&vertexIndices[0], &textureIndices[0], &normalIndices[0],
			&vertexIndices[1], &textureIndices[1], &normalIndices[1],
			&vertexIndices[2], &textureIndices[2], &normalIndices[2]
		);

		if (matched != 9) // If the expected format doesn't match, try other formats.
		{
			matched = sscanf_s(
				line, "f %d/%d %d/%d %d/%d",
				&vertexIndices[0], &textureIndices[0],
				&vertexIndices[1], &textureIndices[1],
				&vertexIndices[2], &textureIndices[2]
			);
		}

		//Face face(vertexIndices, textureIndices, normalIndices, WHITE);
		Face face(vertexIndices, WHITE);
		faces.push_back(face);
	}
}

