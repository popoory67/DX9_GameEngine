#pragma once

#include "Scene.h"


class TestScene : public Scene
{
public:
	TestScene();
	virtual ~TestScene();

	static TestScene* Create();

	GameObject& GetRootGameObject() { return *_rootGameObject; }

private:

	void Init();

private:
	
	GameObject* _rootGameObject = nullptr;

};

