#pragma once

#include <btBulletDynamicsCommon.h>
#include <iostream>
#include "CoreMacros.h"

using namespace std;


class DynamicWorld
{
public:
	DynamicWorld();
	~DynamicWorld();

	static DynamicWorld* Create();

	static DynamicWorld* Get();

	btDiscreteDynamicsWorld* GetDynamicWorld()
	{
		return _dynamicsWorld;
	}

private:

	void Init();

private:

	static DynamicWorld* _instance;

	btBroadphaseInterface* _broadphase;
	btDefaultCollisionConfiguration* _collisionConfiguration;
	btCollisionDispatcher* _dispatcher;
	btSequentialImpulseConstraintSolver* _solver;

	btDiscreteDynamicsWorld* _dynamicsWorld;
};

