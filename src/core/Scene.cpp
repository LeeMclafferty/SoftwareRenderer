#include "Scene.h"
#include "primatives/Triangle.h"
#include "camera/Camera.h"
#include "mesh/Mesh.h"

Scene::Scene()
	:viewportCamera(1)
{
	AddToMeshes(TestingMesh);
	AddToCameras(viewportCamera);
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
	Triangle temp = trianglesToRender[aIndex];
	trianglesToRender[aIndex] = trianglesToRender[bIndex];
	trianglesToRender[bIndex] = temp;
}

Camera* Scene::GetCamera(int cameraId)
{
	auto search = cameraInScene.find(cameraId);

	if (search != cameraInScene.end())
	{
		return search->second.get();
	}
	else
	{
		return nullptr;
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
