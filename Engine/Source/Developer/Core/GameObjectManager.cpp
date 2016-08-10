#include "CorePCH.h"
#include "GameObjectManager.h"

GameObjectManager* GameObjectManager::_instance = nullptr;

GameObjectManager::GameObjectManager()
{
}


GameObjectManager::~GameObjectManager()
{
	SAFE_DELETE( _instance );
}

GameObjectManager& GameObjectManager::Get()
{
	if (!_instance)
	{
		_instance = new GameObjectManager();
	}

	return *_instance;
}

void GameObjectManager::AddGame(const GameObjectPtr gameObject)
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

// GameObject를 모두 삭제해야함
void GameObjectManager::Clear()
{
	_gameVector.clear();
}