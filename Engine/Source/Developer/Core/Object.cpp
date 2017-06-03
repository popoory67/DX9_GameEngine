#include "CorePCH.h"
#include "Object.h"


Object::Object()
{

}

Object::~Object()
{

}

void Object::Destroy(Object* object)
{
	SAFE_DELETE( object );
}