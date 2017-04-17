#pragma once

#include "Scene.h"
#include "GameBehaviour.h"

class SceneManager
{
	using SceneVector = vector<Scene*>;

public:

	~SceneManager();

	static SceneManager& Get();

public:

	static Scene* CreateScene();

	void AddScene( Scene* scene );

	void InitGame();

	void RunUpdate();

	void Clear();

private:

	SceneManager();

private:

	static SceneManager* _instance;

	SceneVector _sceneVector;
};

