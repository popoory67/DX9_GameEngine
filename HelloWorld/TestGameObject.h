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

private:

	MeshRenderer*	_mesh = nullptr;

	TestBehaviour	_testBehaviour; // Create a test game behaviour

};

