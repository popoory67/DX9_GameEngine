#pragma once

#include "Scene.h"
#include "GameBehaviour.h"


class SceneManager
{
	using Scenes = vector<Scene*>;

	enum State
	{
		Start = 0,
		Update,
		Clear
	};

public:

	~SceneManager();

	static SceneManager& Get();

public:

	// The methods for Scene
	void		AddScene( Scene& scene );
	Scene*		AddScene( string sceneName = "Unknown" );

	Scene*		GetScene( UINT sceneNumber ) const;
	Scene*		GetScene( string sceneName ) const;
	Scene*		GetScene( Scene& scene ) const;

	void		CallScene( Scene& scene );

	// The methods for Scenes
	void		InitScene();
	void		UpdateScene();
	void		ClearScene();

private:

	SceneManager();

	void		SearchGameObjects(GameObject* gameObject, State state);

	void		ClearGameObjects(GameObject* gameObject, State state);

	void		RunBehaviours(GameObject* gameObject, State state);

	void		ClearScenes();

private:

	static SceneManager*	_instance;

	Scene*		_currentScene = nullptr;

	Scenes		_scenes;

	// 삭제할 게임 오브젝트들의 리스트

	UINT		_sceneCount = 0;
};

