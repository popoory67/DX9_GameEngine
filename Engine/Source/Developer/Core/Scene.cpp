#include "CorePCH.h"
#include "Scene.h"


Scene::Scene()
{
	_rootGameObjects.reset(new RootGameObjects());
}

Scene::~Scene()
{

}

Scene* Scene::Create()
{
	Scene* scene = new Scene();

	return scene;
}

RootGameObjects& Scene::GetRootGameObjects()
{
	return *_rootGameObjects;
}

void Scene::AddRootGameObject(GameObject* gameObject)
{
	_rootGameObjects->push_back(gameObject);
}

GameObject* Scene::GetRootGameObject(GameObject* gameObject)
{
	auto& ret = find(_rootGameObjects->begin(), _rootGameObjects->end(), gameObject);

	return *ret;
}

GameObject* Scene::GetRootGameObject(string name)
{
	auto& ret = find_if(_rootGameObjects->begin(), _rootGameObjects->end(),
					[&](GameObject* gameObject)
					{
						if (name.compare(gameObject->GetName()))
							return gameObject;
					});

	return *ret;
}