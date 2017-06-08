#include "CorePCH.h"
#include "GameObject.h"


GameObject::GameObject()
{
	_children		= new GameObjects();
	_components		= new Components();
}


GameObject::~GameObject()
{
}

void GameObject::Init()
{

}

void GameObject::AddChild(GameObject* child)
{
	_children->push_back(child);
}

void GameObject::RemoveChild(GameObject* child)
{
	for (auto iter = _children->begin(); iter != _children->end();)
	{
		if (*iter == child)
		{
			SAFE_DELETE(*iter);

			iter = _children->erase(iter++);

			return;
		}

		iter++;
	}
}


void GameObject::AddComponent(Component* component)
{
	component->SetGameObject(this);

	_components->push_back(component);
}

//Component GameObject::GetComponent(string type)
//{
//
//}