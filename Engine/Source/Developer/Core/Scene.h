#pragma once

#include "GameObject.h"


using RootGameObjects = vector<GameObject*>;
using RootGameObjectsPtr = shared_ptr<RootGameObjects>;

class Scene : public GameObject
{
	using GameObject::AddChild;
	using GameObject::GetChildren;
	using GameObject::RemoveChild;

public:
	Scene();
	virtual ~Scene();

	static Scene* Create();

	void SetSceneNumber(unsigned int number)
	{
		_sceneNumber = number;
	}

	RootGameObjects& GetRootGameObjects();

	void AddRootGameObject(GameObject* gameObject);

	GameObject* GetRootGameObject(GameObject* gameObject);
	GameObject* GetRootGameObject(string name);

private:

	RootGameObjectsPtr _rootGameObjects = nullptr;

	unsigned int _sceneNumber = 0;
};

