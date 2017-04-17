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
	GameObject* _gameObject = nullptr; // GameObject�� Add�� �� component�̸� �Ҵ��
	// Transform _transform = _gameObject->transform;

};

