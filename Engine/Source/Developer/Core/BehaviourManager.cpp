#include "CorePCH.h"
#include "BehaviourManager.h"

BehaviourManager* BehaviourManager::_instance = nullptr;

BehaviourManager::BehaviourManager()
{
}


BehaviourManager::~BehaviourManager()
{
	SAFE_DELETE( _instance );
}

BehaviourManager& BehaviourManager::Get()
{
	if (!_instance)
	{
		_instance = new BehaviourManager();
	}

	return *_instance;
}

void BehaviourManager::AddGame( const GameBehaviourPtr gameObject )
{
	_gameVector.push_back(gameObject);
}

void BehaviourManager::InitGame()
{
	for (auto iter = _gameVector.begin(); iter != _gameVector.end(); iter++)
	{
		(*iter)->Start();
	}
}

void BehaviourManager::RunUpdate()
{
	for (auto iter = _gameVector.begin(); iter != _gameVector.end(); iter++)
	{
		(*iter)->Update();
	}
}

// GameObject를 모두 삭제해야함
void BehaviourManager::Clear()
{
	_gameVector.clear();
}