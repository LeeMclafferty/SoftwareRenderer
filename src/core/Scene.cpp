#include "Scene.h"
#include "camera/Camera.h"
#include "mesh/Mesh.h"

Scene::Scene()
	:viewportCamera(std::make_shared<Camera>(1)), testingMesh(std::make_shared<Mesh>())
{
	AddToMeshes(*testingMesh);
	AddToCameras(*viewportCamera);
}

void Scene::AddTriangleToRender(Triangle tri)
{
	trianglesToRender.push_back(tri);
}

void Scene::EmptyTrianlgesToRender()
{
	trianglesToRender.clear();
}

void Scene::SwapTriangleRenderOrder(int aIndex, int bIndex)
{
	std::swap(trianglesToRender[aIndex], trianglesToRender[bIndex]);
}

std::weak_ptr<Camera> Scene::GetCamera(int cameraId)
{
	auto search = cameraInScene.find(cameraId);

	if (search != cameraInScene.end())
	{
		return std::weak_ptr<Camera>(search->second); // No .get() call here
	}
	else
	{
		return std::weak_ptr<Camera>(); // Returns an empty weak_ptr
	}
}

void Scene::AddToCameras(const Camera& cam)
{
	auto result = cameraInScene.emplace(cam.GetId(), std::make_shared<Camera>(cam));

	if (result.second == false)
	{
		std::cout << "Camera ID " << cam.GetId() << " already exists in the map.\n";
	}
}

Mesh* Scene::GetMesh(const std::string& meshKey) const
{
	auto search = meshesInScene.find(meshKey);

	if (search != meshesInScene.end())
	{
		return search->second.get();
	}
	else 
	{
		return nullptr;
	}
}

void Scene::AddToMeshes(const Mesh& mesh)
{
	auto result = meshesInScene.emplace(mesh.GetName(), std::make_shared<Mesh>(mesh));

	if (result.second == false)
	{
		std::cout << "Mesh " << mesh.GetName() << " already exists in the map.\n";
	}
}
