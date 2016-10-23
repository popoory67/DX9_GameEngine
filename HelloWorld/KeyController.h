/**
 * this is test class
 */

#pragma once

#include "Component.h"
#include "InputHeader.h"
#include "XMeshObject.h"

class KeyController : public Component
{
public:
	KeyController();
	~KeyController();

	void KeyInput();

	void KeyInput( XMeshPtr model );

private:

	float _x, _y, _z;
};

