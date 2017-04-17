#pragma once

#include "GameBehaviour.h"
#include "D3DXHeader.h"
#include "RigidBody.h"

class AnimatedUnit : public GameBehaviour
{
public:
	AnimatedUnit( string modelName, string texName, const btVector3& position );
	virtual ~AnimatedUnit();

	virtual void Start();

	virtual void Update();

	MeshModelPtr GetModel() { return _modeling; }

	RigidBody* GetRigidBody() { return _rigid; }

	void CreateXAnimatedModel();

private:

	bool _isClear;

	string _modelName;
	string _texName;

	btVector3 _position;

	XAnimatedObjectPtr _modeling;
	RigidBody* _rigid;
};

