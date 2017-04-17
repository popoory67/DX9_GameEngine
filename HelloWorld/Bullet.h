#pragma once

#include "D3DXHeader.h"
#include "RigidBody.h"


class Bullet
{
public:
	Bullet();
	~Bullet();

	RigidBody* GetRigidBody() { return _rigid; }

	void CreateBullet();
	void SetDetectionFlag();

private:

	RigidBody* _rigid;
};