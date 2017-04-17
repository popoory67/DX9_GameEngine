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

	void AddChild(GameObject* child);
	void RemoveChild(GameObject* child);
	GameObjects& GetChildren() { return _children; }
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
				// component = nullptr;

				continue;
			}

			return *component;
		}
	}

	//Component GetComponent(string type)
	//{

	//}

	/**
	BroadcastMessage	Calls the method named methodName on every MonoBehaviour in this game object or any of its children.
	CompareTag	Is this game object tagged with tag ?
	GetComponent	Returns the component of Type type if the game object has one attached, null if it doesn't.
	GetComponentInChildren	Returns the component of Type type in the GameObject or any of its children using depth first search.
	GetComponentInParent	Returns the component of Type type in the GameObject or any of its parents.
	GetComponents	Returns all components of Type type in the GameObject.
	GetComponentsInChildren	Returns all components of Type type in the GameObject or any of its children.
	GetComponentsInParent	Returns all components of Type type in the GameObject or any of its parents.
	SendMessage	Calls the method named methodName on every MonoBehaviour in this game object.
	SendMessageUpwards	Calls the method named methodName on every MonoBehaviour in this game object and on every ancestor of the behaviour.
	*/


private:

	GameObjects _children; // binary tree

	Components _components;

};

