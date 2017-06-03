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

	static Scene* Create(unsigned int number = 0, string name = "Unknown");

	// Get scene data
	unsigned int GetSceneNumber() { return _sceneNumber; }
	string GetSceneName() { return _sceneName; }

	// Set scene data
	void SetSceneNumber(unsigned int number) { _sceneNumber = number; }
	void SetSceneName(string name) { _sceneName = name; }

	// The methods of root game object
	RootGameObjects& GetRootGameObjects();

	void AddRootGameObject(GameObject* gameObject);

	GameObject* GetRootGameObject(GameObject* gameObject);
	GameObject* GetRootGameObject(string name);

private:

	RootGameObjectsPtr _rootGameObjects = nullptr;

	unsigned int _sceneNumber = 0;
	string _sceneName;
};

