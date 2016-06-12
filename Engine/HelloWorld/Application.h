#pragma once

#include "GameObject.h"


class GameManager : public GameObject
{
public:

	GameManager();

	~GameManager();

	virtual void Start();

	virtual void Update();

	void KeyInput();

	virtual void Release();

private:

};

