#include "RenderPCH.h"
#include "GameObject.h"


GameObject::GameObject()
{

}

GameObject::~GameObject()
{

}

void GameObject::AddComponent(GameObject* component)
{
	_componentVector.push_back(component);
}

void GameObject::Start()
{

}

void GameObject::Update()
{

}

void GameObject::Release()
{

}