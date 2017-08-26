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

	SAFE_DELETE( _currentScene );

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

void SceneManager::ClearScenes()
{
	for (auto scene = _scenes.begin(); scene != _scenes.end();)
	{
		_currentScene = *scene;

		ClearScene();

		SAFE_DELETE(*scene);
		scene = _scenes.erase(scene);
	}

	_scenes.clear();
}

void SceneManager::AddScene( Scene& scene )
{
	scene.SetSceneNumber(_sceneCount);
	++_sceneCount;

	_scenes.push_back(&scene);

	if (_sceneCount == 1)
	{
		_currentScene = &scene;
	}
}

Scene* SceneManager::AddScene(string sceneName)
{
	Scene* scene = Scene::Create(_sceneCount, sceneName);
	++_sceneCount;

	_scenes.push_back(scene);

	if (_sceneCount == 1)
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
						{
							return scene;
						}
					});

	return *ret;
}

Scene* SceneManager::GetScene(string sceneName) const
{
	auto ret = find_if(_scenes.begin(), _scenes.end(),
					[&](Scene* scene)
					{
						if (sceneName == scene->GetSceneName())
						{
							return scene;
						}
					});

	return *ret;
}

Scene* SceneManager::GetScene(Scene& scene) const
{
	auto ret = find_if(_scenes.begin(), _scenes.end(), 
					[&](Scene* iter)
					{
						if (iter == &scene)
						{
							return iter;
						}
					});

	return *ret;
}


void SceneManager::CallScene(Scene& scene)
{
	_currentScene = &scene;
}

void SceneManager::InitScene()
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

void SceneManager::UpdateScene()
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

void SceneManager::ClearScene()
{
	if (!_currentScene)
	{
		assert(Util::ErrorMessage("Null exception for current scene(Clear)"));
		return;
	}

	// Scene의 게임 오브젝트들을 정리한다
	auto roots = _currentScene->GetRootGameObjects();

	for (auto root = roots.begin(); root != roots.end();)
	{
		ClearGameObjects(*root, Clear);

		RunBehaviours(*root, Clear);

		SAFE_DELETE(*root);
		root = roots.erase(root);
	}

	roots.clear();

	// Scenes에서 현재 Scene을 삭제
	for (auto scene = _scenes.begin(); scene != _scenes.end();)
	{
		if (*scene == _currentScene)
		{
			SAFE_DELETE(*scene);
			scene = _scenes.erase(scene);

			--_sceneCount;
			break;
		}

		++scene;
	}

	if (_sceneCount > 0)
	{
		_currentScene = *_scenes.begin();
	}

	//else
	//{
	//	assert(Util::ErrorMessage("Scene is empty."));
	//}
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

void SceneManager::ClearGameObjects(GameObject* gameObject, State state)
{
	// child object
	auto children = gameObject->GetChildren();

	if (children->empty())
	{
		return;
	}

	for (auto child = children->begin(); child != children->end();)
	{
		ClearGameObjects(*child, state);
		RunBehaviours(*child, state);

		SAFE_DELETE(*child);
		child = children->erase(child);
	}

	children->clear();
	SAFE_DELETE(children);
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