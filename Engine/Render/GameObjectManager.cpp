#include "RenderPCH.h"
#include "GameObjectManager.h"

GameObjectManager* GameObjectManager::_instance = nullptr;

GameObjectManager::GameObjectManager()
{
}


GameObjectManager::~GameObjectManager()
{
	if (_instance)
	{
		SAFE_DELETE(_instance);
	}
}

GameObjectManager& GameObjectManager::Get()
{
	if (!_instance)
	{
		_instance = new GameObjectManager();
	}

	return *_instance;
}

void GameObjectManager::AddGame(GameObjectPtr gameObject)
{
	_gameVector.push_back(gameObject);
}

void GameObjectManager::InitGame()
{
	for (auto iter = _gameVector.begin(); iter != _gameVector.end(); iter++)
	{
		(*iter)->Start();
	}
}

void GameObjectManager::RunUpdate()
{
	for (auto iter = _gameVector.begin(); iter != _gameVector.end(); iter++)
	{
		(*iter)->Update();
	}
}

void GameObjectManager::Clear()
{
	_gameVector.clear();
}