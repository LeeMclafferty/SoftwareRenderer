#include "Mesh.h"
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <colors/Colors.h>

/* Default Constructor constructs cube mesh */
Mesh::Mesh()
	:rotation(Vector3D{0.f, 0.f, 0.f}), scale(Vector3D{1.f, 1.f, 1.f}), translation(Vector3D{1.f, 1.f, 1.f}), name("Default Cube")
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
		{ {1, 2, 3}, CORAL },
		{ {1, 3, 4}, CORAL },
		// right
		{ {4, 3, 5}, SEA_GREEN },
		{ {4, 5, 6}, SEA_GREEN },
		// back
		{ {6, 5, 7}, SKY_BLUE },
		{ {6, 7, 8}, SKY_BLUE},
		// left
		{ {8, 7, 2}, GOLD },
		{ {8, 2, 1}, GOLD},
		// top
		{ {2, 7, 5}, MEDIUM_PURPLE },
		{ {2, 5, 3}, MEDIUM_PURPLE },
		// bottom
		{ {6, 8, 1}, DEEP_PINK },
		{ {6, 1, 4}, DEEP_PINK }
	};
}

Mesh::Mesh(char* file, std::string meshName)
	:name(meshName)
{
	LoadObjData(file);
}

void Mesh::LoadObjData(char* filename)
{
	std::ifstream file(filename);
	std::string line;

	while (std::getline(file, line))
	{
		std::istringstream iss(line);
		std::string prefix;
		iss >> prefix;

		if (prefix == "v")
		{
			Vector3D vertex{0, 0, 0};
			iss >> vertex.x >> vertex.y >> vertex.z;
			vertices.push_back(vertex);
		}
		else if (prefix == "f")
		{
			int vertex[3];
			int texture_coord[3];
			int normals[3];

			char slash; // For reading slashes

			for (int i = 0; i < 3; ++i)
			{
				iss >> vertex[i] >> slash >> texture_coord[i] >> slash >> normals[i];
			}

			Face face (
				std::array<int, 3> {
					vertex[0],
					vertex[1],
					vertex[2],
				},
				WHITE
			);
			faces.push_back(face);
		}
	}
}
