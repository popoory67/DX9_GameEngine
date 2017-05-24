#pragma once

#include "Object.h"
#include "Component.h"

class Component;

class GameObject : public Object
{
	using GameObjects = vector<GameObject*>;
	using Components = vector<Component*>;

public:
	GameObject();
	virtual ~GameObject();

	// The methods about game objects
	void AddChild(GameObject* child);
	void RemoveChild(GameObject* child);
	GameObjects& GetChildren() { return _children; }

	// The methods about components
	Components& GetComponents() { return _components; }
	void AddComponent(Component* component);

	/**
	* Find component and return it
	* @return the type of component
	*/
	template<class Type>
	Type& GetComponent()
	{
		for (auto iter = _components.begin(); iter != _components.end(); iter++)
		{
			auto component = dynamic_cast<Type*>(*iter);

			if (!component)
			{
				delete (component);
				continue;
			}

			return *component;
		}
	}

	//Component GetComponent(string type)
	//{

	//}

private:

	GameObjects _children; // binary tree

	Components _components;

};

