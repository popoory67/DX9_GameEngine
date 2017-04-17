#pragma once

#include "Component.h"

// custom component
class GameBehaviour : public Component
{
public:
	GameBehaviour();
	virtual ~GameBehaviour();

	virtual void Start();

	virtual void Update();

	virtual void Release();
};

