#pragma once

#include "Scene.h"
#include "GameBehaviour.h"

class SceneManager
{
	using Scenes = vector<Scene*>;

public:

	~SceneManager();

	static SceneManager& Get();

public:

	void AddScene( Scene* scene );

	void InitScenes();

	void UpdateScenes();

	void ClearScenes();

private:

	SceneManager();

private:

	static SceneManager* _instance;

	Scenes _scenes;

	unsigned int _sceneCount = 0;
};

