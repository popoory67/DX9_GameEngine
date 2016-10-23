#pragma once

#include "GameBehaviour.h"

#include "D3DXHeader.h"
#include "Collision.h"

class MyGameManager : public GameBehaviour
{
public:

	MyGameManager();

	~MyGameManager();

	virtual void Start();

	virtual void Update();

	virtual void Release();

private:

	XAnimatedObjectPtr _warrior; //XAnimatedObjectPtr _warrior;
	XMeshPtr _object; //XMeshPtr _object;
	//MeshModelPtr _bb8;

	Collision* _col;

	RigidBody* _fallRigid;
	RigidBody* _fallRigid2;
	RigidBody* _planeRigid;

	float _x, _y, _z;
};

