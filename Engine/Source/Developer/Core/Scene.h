#pragma once

#include "GameObject.h"


class Scene : public GameObject
{
	using RootGameObjects = vector<GameObject*>;

public:
	Scene();
	virtual ~Scene();

	static Scene* Create();

	RootGameObjects& GetRoots()
	{
		return *_rootGameObjects;
	}

	void AddRootGameObject(GameObject* gameObject)
	{
		_rootGameObjects->push_back(gameObject);
	}

	//using GameObject::AddChild;

protected:

	void Init();

private:

	RootGameObjects* _rootGameObjects = nullptr;

	unsigned int _sceneNumber;


};

