#pragma once

#include "Scene.h"
#include "TestGameObject.h"

class TestScene : public Scene
{
public:
	TestScene();
	virtual ~TestScene();

	static TestScene* Create();

private:

	void Init();

private:

	TestGameObject* _gameObject;
	//TestGameObject* _gameObject[5];
	//TestGameObject* _child[5];
};

