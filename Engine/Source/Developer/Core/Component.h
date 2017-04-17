#pragma once

#include "Object.h"
//#include "GameObject.h"

class GameObject;

class Component : public Object
{


public:
	Component();
	virtual ~Component();

	template<class Type>
	Type& GetComponent()
	{
		if (!_gameObject)
			return nullptr;

		return _gameObject->GetComponent<Type>();
	}

	//Component GetComponent(string type)
	//{

	//}

protected:

	string _tag = "";
	GameObject* _gameObject = nullptr; // GameObject에 Add가 된 component이면 할당됨
	// Transform _transform = _gameObject->transform;

};

