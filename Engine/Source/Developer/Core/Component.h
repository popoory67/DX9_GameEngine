#pragma once

#include "Object.h"

class GameObject;

/**
 * The component class is a prototype of all functions. 
 */
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

	void		AddObserver();
	void		SendMessage();


	void		SetGameObject( GameObject* gameObject )	{ _gameObject = gameObject; } // ���� ����, ���� ����

	GameObject*	GetGameObject()							{ return _gameObject; }

protected:

	string			_tag		= "";

	GameObject*		_gameObject = nullptr; // GameObject�� Add�� �� component�̸� �Ҵ��

};

