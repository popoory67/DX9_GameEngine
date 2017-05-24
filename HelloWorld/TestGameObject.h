#pragma once

#include "GameObject.h"
#include "MeshRenderer.h"

// This is test game object to include 3d mesh component
class TestGameObject : public GameObject
{
public:
	TestGameObject();
	virtual ~TestGameObject();

	void Init();

private:

	MeshRenderer* _mesh = nullptr;

};

