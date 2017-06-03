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

	void		CallScene( Scene& scene );

	// The methods for Scenes
	void		InitScenes();
	void		UpdateScenes();
	void		ClearScenes();

private:

	SceneManager();

	void		SearchGameObjects(GameObject* gameObject, State state);

	void		RunBehaviours(GameObject* gameObject, State state);

private:

	static SceneManager*	_instance;

	Scene*		_currentScene = nullptr;

	Scenes		_scenes;

	UINT		_sceneCount = 0;
};

