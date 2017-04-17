#include "CorePCH.h"
#include "Scene.h"


Scene::Scene()
{
}


Scene::~Scene()
{
}

Scene* Scene::Create()
{
	Scene* scene = new Scene();

	scene->Init();

	return scene;
}

void Scene::Init()
{
	_rootGameObjects = new RootGameObjects();
}
