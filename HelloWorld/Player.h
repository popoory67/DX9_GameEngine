#pragma once

#include "GameBehaviour.h"
#include "D3DXHeader.h"
#include "Bullet.h"

#define SPEED			4

class Player : public GameBehaviour
{
public:
	Player();
	virtual ~Player();

	virtual void Update();

	void KeyInput();

private:

	Bullet* _bullet;
};
