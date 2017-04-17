#include "CorePCH.h"
#include "SceneManager.h"

SceneManager* SceneManager::_instance = nullptr;

SceneManager::SceneManager()
{
}


SceneManager::~SceneManager()
{
	Clear();

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
	_sceneVector.push_back(scene);
}

void SceneManager::InitGame()
{
	// Scene vector
	for (auto iter = _sceneVector.begin(); iter != _sceneVector.end(); iter++)
	{
		auto rootGameObjectVector = (*iter)->GetRoots(); // Root game object vector

		for (auto sceneIter = rootGameObjectVector.begin(); sceneIter != rootGameObjectVector.end(); sceneIter++)
		{
			auto components = (*sceneIter)->GetComponents();

			for (auto componentsIter = components.begin(); componentsIter != components.end(); componentsIter++)
			{
				// Run game behaviour
				dynamic_cast<GameBehaviour*>(*componentsIter)->Start();
			}

		}
	}
}

void SceneManager::RunUpdate()
{
	for (auto iter = _sceneVector.begin(); iter != _sceneVector.end(); iter++)
	{
		auto rootGameObjectVector = (*iter)->GetRoots();

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

void SceneManager::Clear()
{
	for (auto iter = _sceneVector.begin(); iter != _sceneVector.end(); iter++)
	{
		auto rootGameObjectVector = (*iter)->GetRoots();

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

	_sceneVector.clear();
}