#pragma once

#include "GameObject.h"

class GameManager : public GameObject
{
public:

	GameManager();

	~GameManager();

	void Start();

	void Update();

	void KeyInput();

	void Release();

private:

};