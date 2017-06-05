#pragma once

#include "GameObject.h"
#include "MeshRenderer.h"
#include "TestBehaviour.h"

// This is test game object to include 3d mesh component
class TestGameObject : public GameObject
{
public:
	TestGameObject();
	virtual ~TestGameObject();

	virtual void	Init() override;

	MeshModel*		GetModel()			{ return _meshRenderer->GetModel(); }

private:

	MeshRenderer*	_meshRenderer = nullptr;

	TestBehaviour*	_testBehaviour;

};

