#pragma once

#include "Component.h"

/**
 * The game behaviour is not object, only defines behaviour.
 * Using components of the game object to which belongs this class, you can define the object's behaviour.
 */
class GameBehaviour : public Component
{
public:
	GameBehaviour();
	virtual ~GameBehaviour();

	virtual void	Start();

	virtual void	Update();

	virtual void	Release();
};

