#pragma once

#include "GameObject.h"

using GameObjectPtr		= shared_ptr< GameObject >;
using GameObjectVector	= vector< GameObjectPtr >;

class GameObjectManager
{
public:

	~GameObjectManager();

	static GameObjectManager& Get();

public:

	void AddGame(const GameObjectPtr gameObject);

	void InitGame();

	void RunUpdate();

	void Clear();

private:

	GameObjectManager();

private:

	static GameObjectManager* _instance;

	GameObjectVector _gameVector;
};

