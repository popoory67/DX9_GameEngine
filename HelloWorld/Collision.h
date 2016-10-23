#pragma once

#include "Component.h"
#include "MessageHeader.h"

#include "DynamicWorld.h"
#include "RigidBody.h"

class Collision : public Component
{
public:
	Collision();
	~Collision();

	void Init();

	void SimulateGravity( function<void( float )> func, RigidBody* rigidbody );
	
private:

	int _i = 0;
};

