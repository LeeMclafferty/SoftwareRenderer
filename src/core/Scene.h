#pragma once
#include <vector>
#include <unordered_map>
#include <string.h>
#include <memory>
#include "primatives/Triangle.h"
#include "camera/Camera.h"
//class Camera;
class Mesh;

class Scene
{
public:
	Scene();

	const std::vector<Triangle> GetTrianglesToRender() const { return trianglesToRender; }
	void AddTriangleToRender(Triangle tri);
	void EmptyTrianlgesToRender();
	void SwapTriangleRenderOrder(int aIndex, int bIndex);

	const std::unordered_map<int, std::shared_ptr<Camera>> GetAllCameras() const { return cameraInScene; }
	std::weak_ptr<Camera> GetViewportCamera() { return GetCamera(viewportCamera->GetId()); }
	std::weak_ptr<Camera> GetCamera(int cameraId);
	void AddToCameras(const Camera& cam);

	std::unordered_map<std::string, std::shared_ptr<Mesh>> GetAllMeshes() const { return meshesInScene; }
	class Mesh* GetMesh(const std::string& meshKey) const;
	void AddToMeshes(const Mesh& mesh);

private:
	std::vector<Triangle> trianglesToRender;
	std::unordered_map<int, std::shared_ptr<Camera>> cameraInScene;
	std::unordered_map<std::string, std::shared_ptr<Mesh>> meshesInScene;
	
	std::shared_ptr<Camera> viewportCamera;
	std::shared_ptr<Mesh> testingMesh;
};

