#pragma once

#include "Scene.h"


class TestScene : public Scene
{
public:
	TestScene();

	virtual ~TestScene();

	static TestScene* Create();

private:

};

