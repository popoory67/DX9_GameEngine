#pragma once

#include "GameBehaviour.h"

using ComponentPtr			= shared_ptr< Component >;
using ComponentVector		= vector< ComponentPtr >;

using GameBehaviourPtr		= shared_ptr< GameBehaviour >;
using GameBehaviourVector	= vector< GameBehaviourPtr >;

class BehaviourManager
{
public:

	~BehaviourManager();

	static BehaviourManager& Get();

public:

	void AddGame( const GameBehaviourPtr gameObject );

	void InitGame();

	void RunUpdate();

	void Clear();

private:

	BehaviourManager();

private:

	static BehaviourManager* _instance;

	GameBehaviourVector _gameVector;
};

