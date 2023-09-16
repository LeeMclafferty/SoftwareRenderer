#pragma once
#include <vector>
#include <iostream>
#include "SDL.h"
#include "vectors/VectorTypes.h"
#include "Face.h"
#include "texture/Texture.h"

class Mesh
{
public:
	Mesh();
	Mesh(std::string file, std::string meshName);

	std::vector<Vector3D> GetVertices() const { return vertices; }
	std::vector<Face> GetFaces() const { return faces; }

	Vector3D GetRotation() const { return rotation; }
	Vector3D GetScale() const { return scale; }
	Vector3D GetLocation() const { return translation; }
	Texture2D GetTexture() const { return texture; }

	void SetRotation(Vector3D rot) { rotation = rot; }
	void SetScale(Vector3D newScale) { scale = newScale; }
	void SetLocation(Vector3D trans) { translation = trans; }
	
	std::string GetName() const { return name; }
	void SetMeshName(std::string newName) { name = newName; }

private:
	std::vector<Vector3D> vertices;
	std::vector<Face> faces;
	Vector3D rotation;
	Vector3D scale;
	Vector3D translation;
	std::string name;

	void LoadObjData(const std::string& filename);
	void PushVerticies(char* line);
	void PushFaces(char* line);

	Texture2D texture;
};

