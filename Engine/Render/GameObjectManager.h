#pragma once

#include "GameObject.h"

typedef shared_ptr<GameObject>	GameObjectPtr;
typedef vector<GameObjectPtr>	GameObjectVector;

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

