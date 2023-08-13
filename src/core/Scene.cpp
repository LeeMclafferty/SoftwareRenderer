#include "Scene.h"
#include "camera/Camera.h"
#include "mesh/Mesh.h"

Scene::Scene()
	:viewportCamera(1), testingMesh()
{
	AddToMeshes(&testingMesh);
	AddToCameras(&viewportCamera);
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

Camera* Scene::GetCamera(int cameraId)
{
	auto search = cameraInScene.find(cameraId);

	if (search != cameraInScene.end())
	{
		return search->second; // Return a reference to the Camera
	}
	else
	{
		throw std::runtime_error("Camera not found");
	}
}

void Scene::AddToCameras(Camera* cam)
{
	auto result = cameraInScene.emplace(cam->GetId(), cam);

	if (result.second == false)
	{
		std::cout << "Camera ID " << cam->GetId() << " already exists in the map.\n";
	}
}

 Mesh* Scene::GetMesh(const std::string& meshKey) const
{
	auto search = meshesInScene.find(meshKey);

	if (search != meshesInScene.end())
	{
		return search->second; // Return a reference to the Mesh
	}
	else
	{
		throw std::runtime_error("Mesh not found");
	}
}

void Scene::AddToMeshes(Mesh* mesh)
{
	auto result = meshesInScene.emplace(mesh->GetName(), mesh);

	if (result.second == false)
	{
		std::cout << "Mesh " << mesh->GetName() << " already exists in the map.\n";
	}
}
