#pragma once

#include "CorePCH.h"

class Object
{

public:
	Object();
	virtual ~Object();

	unsigned int GetInstanceID();
	string GetName();

	static void Destroy(Object* object);

protected:

	unsigned int _id = 0;
	string _name = "";

};

