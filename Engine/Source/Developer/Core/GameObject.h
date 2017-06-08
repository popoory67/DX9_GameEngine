#pragma once

#include "Object.h"
#include "Component.h"

/**
 * This class represents original form of all game objects.
 * Expresses an object, not game action.
 */
class GameObject : public Object
{
	using GameObjects	= vector<GameObject*>;
	using Components	= vector<Component*>;

public:
	GameObject();
	virtual ~GameObject();

	// If you want to include any behaviours or components, 
	// you must declare 'add the component' in this function.
	virtual void Init();

	void	SetNumber(unsigned int number)	{ _number = number; }
	void	SetName(string name)			{ _name = name; }

	UINT	GetNumber()	const				{ return _number; }
	string	GetName() const					{ return _name; }

	// The methods for game objects
	GameObjects*	GetChildren()			{ return _children; }

	void			AddChild(GameObject* child);
	void			RemoveChild(GameObject* child);

	// The methods for components
	Components*		GetComponents()			{ return _components; }

	void			AddComponent(Component* component);
	
	/**
	* Find component and return it
	* @return the type of component
	*/
	template<class Type>
	Type* GetComponent()
	{
		if (_components->empty())
		{
			assert(Util::ErrorMessage("The components is null"));
			return nullptr;
		}

		for (auto iter = _components->begin(); iter != _components->end(); iter++)
		{
			auto component = dynamic_cast<Type*>(*iter);

			if (component)
			{
				return component;
			}
		}

		string typeName = typeid(Type).name();
		assert(Util::ErrorMessage("Not exist : " + typeName));
	}
	
	//Component GetComponent(string type)
	//{

	//}

	// message


private:

	GameObjects*	_children;

	Components*		_components;

	// Datas
	string			_name;
	UINT			_number;

};

