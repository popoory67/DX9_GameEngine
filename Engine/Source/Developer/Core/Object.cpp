#include "CorePCH.h"
#include "Object.h"


Object::Object()
{

}

Object::~Object()
{

}

unsigned int Object::GetInstanceID()
{
	return 0;
}

string Object::GetName()
{
	return "";
}

void Object::Destroy(Object* object)
{
	SAFE_DELETE( object );
}