#pragma once

#include "CorePCH.h"

class Object
{

public:
	Object();
	virtual ~Object();

	static void		Destroy(Object* object);
};

