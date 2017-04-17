#pragma once

#include "GameBehaviour.h"
#include "D3DXHeader.h"
#include "RigidBody.h"

class Plane : public GameBehaviour
{
public:
	Plane();
	virtual ~Plane();

	virtual void Start();

	virtual void Update();

private:

	MeshModelPtr _modeling;

	RigidBody* _rigid;

};

