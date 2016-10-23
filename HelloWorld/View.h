#pragma once

#include "Message.h"
#include "DynamicWorld.h"

#define COLLISION_TEST "collision_test"

class View
{
public:

	View();
	~View();

	static View* Create();

	void Init();
	void Render( Message* msg );

private:

	void CollisionTest();

	DynamicWorld* test;

};

