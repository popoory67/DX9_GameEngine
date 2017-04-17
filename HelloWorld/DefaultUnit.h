#pragma once

#include "GameBehaviour.h"
#include "D3DXHeader.h"
#include "RigidBody.h"


enum ModelType
{
	X_DEFAULT = 0,
	OBJ_DEFAULT
};

class DefaultUnit : public GameBehaviour
{
public:
	DefaultUnit( string modelName, string texName, const btVector3& position, ModelType type );
	virtual ~DefaultUnit();

	virtual void Start();

	virtual void Update();

	MeshModelPtr GetModel() { return _modeling; }

	RigidBody* GetRigidBody() { return _rigid; }

	void CreateXDefaultModel();
	void CreateObjDefaultModel();

private:

	bool _isClear;

	ModelType _type;

	string _modelName;
	string _texName;

	btVector3 _position;

	MeshModelPtr _modeling;
	RigidBody* _rigid;
};

