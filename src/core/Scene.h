#pragma once
#include <vector>
#include <unordered_map>
#include <string.h>
#include "camera/Camera.h"
#include "primatives/Triangle.h"
#include "mesh/Mesh.h"

class Mesh;

class Scene
{
public:
	Scene();

	const std::vector<Triangle> GetTrianglesToRender() const { return trianglesToRender; }
	void AddTriangleToRender(Triangle tri);
	void EmptyTrianlgesToRender();
	void SwapTriangleRenderOrder(int aIndex, int bIndex);

	std::unordered_map<int, Camera*> GetAllCameras() const { return cameraInScene; }
	Camera* GetViewportCamera() { return &viewportCamera; }
	Camera* GetCamera(int cameraId);
	void AddToCameras(Camera* cam);

	std::unordered_map<std::string, Mesh*> GetAllMeshes() const { return meshesInScene; }
	Mesh* GetMesh(const std::string& meshKey) const;
	void AddToMeshes(Mesh* mesh);

private:
	std::vector<Triangle> trianglesToRender;
	std::unordered_map<int, Camera*> cameraInScene;
	std::unordered_map<std::string, Mesh*> meshesInScene;
	
	Camera viewportCamera;
	Mesh testingMesh;
};

