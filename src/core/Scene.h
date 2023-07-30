#pragma once
#include <vector>
#include <unordered_map>
#include <string.h>

class Scene
{
public:
	Scene();

	const std::vector<Triangle> GetTrianglesToRender() const { return trianglesToRender; }
	void AddTriangleToRender(Triangle tri);
	void EmptyTrianlgesToRender();
	void SwapTriangleRenderOrder(int aIndex, int bIndex);

	const std::unordered_map<int, std::shared_ptr<Camera>> GetAllCameras() const { return cameraInScene; }
	Camera* GetViewportCamera() { return GetCamera(viewportCamera.GetId()); }
	Camera* GetCamera(int cameraId);
	void AddToCameras(const Camera& cam);

	std::unordered_map<std::string, std::shared_ptr<Mesh>> GetAllMeshes() const { return meshesInScene; }
	class Mesh* GetMesh(const std::string& meshKey) const;
	void AddToMeshes(const Mesh& mesh);

private:
	std::vector<Triangle> trianglesToRender;
	std::unordered_map<int, std::shared_ptr<Camera>> cameraInScene;
	std::unordered_map<std::string, std::shared_ptr<Mesh>> meshesInScene;
	
	class Camera viewportCamera;
	class Mesh TestingMesh;
};

