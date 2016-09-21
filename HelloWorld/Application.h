#pragma once

#include "GameObject.h"

#include "D3DXHeader.h"

class GameManager : public GameObject
{
public:

	GameManager();

	~GameManager();

	virtual void Start();

	virtual void Update();

	virtual void Release();

	void KeyInput();

private:

	XAnimatedObjectPtr _warrior;
	XMeshPtr _object;

	float x, y, z;
};

