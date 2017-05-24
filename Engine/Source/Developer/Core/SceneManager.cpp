#include "CorePCH.h"
#include "SceneManager.h"

SceneManager* SceneManager::_instance = nullptr;

SceneManager::SceneManager()
{
}


SceneManager::~SceneManager()
{
	ClearScenes();

	SAFE_DELETE( _instance );
}

SceneManager& SceneManager::Get()
{
	if (!_instance)
	{
		_instance = new SceneManager();
	}

	return *_instance;
}

void SceneManager::AddScene( Scene* scene )
{
	scene->SetSceneNumber(_sceneCount);
	_sceneCount++;

	_scenes.push_back(scene);
}

void SceneManager::InitScenes()
{
	// The vector of scenes
	for (auto iter = _scenes.begin(); iter != _scenes.end(); iter++)
	{
		auto rootGameObjectVector = (*iter)->GetRootGameObjects(); 

		// The vector of root game objects
		for (auto sceneIter = rootGameObjectVector.begin(); sceneIter != rootGameObjectVector.end(); sceneIter++)
		{
			// The vector of child game objects

			auto components = (*sceneIter)->GetComponents();

			// The vector of components
			for (auto componentsIter = components.begin(); componentsIter != components.end(); componentsIter++)
			{
				// Run game behaviour
				dynamic_cast<GameBehaviour*>(*componentsIter)->Start();
			}

		}
	}
}

void SceneManager::UpdateScenes()
{
	for (auto iter = _scenes.begin(); iter != _scenes.end(); iter++)
	{
		auto rootGameObjectVector = (*iter)->GetRootGameObjects();

		for (auto sceneIter = rootGameObjectVector.begin(); sceneIter != rootGameObjectVector.end(); sceneIter++)
		{
			auto components = (*sceneIter)->GetComponents();

			for (auto componentsIter = components.begin(); componentsIter != components.end(); componentsIter++)
			{
				// Run game behaviour
				dynamic_cast<GameBehaviour*>(*componentsIter)->Update();
			}
		}
	}
}

void SceneManager::ClearScenes()
{
	for (auto iter = _scenes.begin(); iter != _scenes.end(); iter++)
	{
		auto rootGameObjectVector = (*iter)->GetRootGameObjects();

		for (auto sceneIter = rootGameObjectVector.begin(); sceneIter != rootGameObjectVector.end(); sceneIter++)
		{
			auto components = (*sceneIter)->GetComponents();

			for (auto componentsIter = components.begin(); componentsIter != components.end(); componentsIter++)
			{
				// Run game behaviour
				dynamic_cast<GameBehaviour*>(*componentsIter)->Release();
			}
		}
	}

	_scenes.clear();
}