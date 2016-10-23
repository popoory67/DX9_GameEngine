#include "CorePCH.h"
#include "Component.h"
#include "BehaviourManager.h"

Component::Component() : _name( "" )
{

}

Component::~Component()
{

}

void Component::AddComponent( Component* component )
{
	_componentVector.push_back( component );
}