#include "CorePCH.h"
#include "SceneManager.h"
#include "ThreadManager.h"
#include "Log.h"

SceneManager* SceneManager::_instance = nullptr;

SceneManager::SceneManager()
{
}


SceneManager::~SceneManager()
{
	ClearScenes();

	SAFE_DELETE(_currentScene);

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

void SceneManager::AddScene( Scene& scene )
{
	scene.SetSceneNumber(_sceneCount);
	++_sceneCount;

	_scenes.push_back(&scene);

	if (_scenes.size() == 1)
	{
		_currentScene = &scene;
	}
}

Scene* SceneManager::AddScene(string sceneName)
{
	Scene* scene = Scene::Create(_sceneCount, sceneName);
	++_sceneCount;

	_scenes.push_back(scene);

	if (_scenes.size() == 1)
	{
		_currentScene = scene;
	}

	return scene;
}

Scene* SceneManager::GetScene(UINT sceneNumber) const
{
	auto ret = find_if(_scenes.begin(), _scenes.end(),
					[&](Scene* scene) 
					{ 
						if (sceneNumber == scene->GetSceneNumber())
							return scene;
					});

	return *ret;
}

Scene* SceneManager::GetScene(string sceneName) const
{
	auto ret = find_if(_scenes.begin(), _scenes.end(),
					[&](Scene* scene)
					{
						if (sceneName == scene->GetSceneName())
							return scene;
					});

	return *ret;
}

void SceneManager::CallScene(Scene& scene)
{
	_currentScene = &scene;
}

void SceneManager::InitScenes()
{
	if (!_currentScene)
	{
		assert(Util::ErrorMessage("Null exception for current scene(Init)"));
		return;
	}

	auto roots = _currentScene->GetRootGameObjects();

	for (auto root = roots.begin(); root != roots.end(); ++root)
	{
		SearchGameObjects(*root, Start);

		RunBehaviours(*root, Start);
	}
}

void SceneManager::UpdateScenes()
{	
	if (!_currentScene)
	{
		assert(Util::ErrorMessage("Null exception for current scene(Update)"));
		return;
	}

	auto roots = _currentScene->GetRootGameObjects();

	for (auto root = roots.begin(); root != roots.end(); ++root)
	{
		SearchGameObjects(*root, Update);

		RunBehaviours(*root, Update);
	}
}

void SceneManager::ClearScenes()
{
	if (!_currentScene)
	{
		assert(Util::ErrorMessage("Null exception for current scene(Clear)"));
		return;
	}

	auto roots = _currentScene->GetRootGameObjects();

	for (auto root = roots.begin(); root != roots.end(); ++root)
	{
		SearchGameObjects(*root, Clear);

		RunBehaviours(*root, Clear);
	}

	_scenes.clear();
}

void SceneManager::SearchGameObjects(GameObject* gameObject, State state)
{
	if (state == Start)
	{
		gameObject->Init();
	}

	// child object
	auto children = gameObject->GetChildren();

	if (children->empty())
	{
		return;
	}

	for (auto child = children->begin(); child != children->end(); ++child)
	{
		SearchGameObjects(*child, state);

		RunBehaviours(*child, state);
	}
};

void SceneManager::RunBehaviours(GameObject* gameObject, State state)
{
	auto components = gameObject->GetComponents();

	for (auto component = components->begin(); component != components->end(); ++component)
	{
		auto gameBehaviour = dynamic_cast<GameBehaviour*>(*component);

		if (gameBehaviour)
		{
			switch (state)
			{
			case Start:
				gameBehaviour->Start();
				break;

			case Update:
				gameBehaviour->Update();
				break;

			case Clear:
				gameBehaviour->Release();
				break;
			}
		}
	}
}