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


	void		SetGameObject( GameObject* gameObject )	{ _gameObject = gameObject; } // 얕은 복사, 깊은 복사

	GameObject*	GetGameObject()							{ return _gameObject; }

protected:

	string			_tag		= "";

	GameObject*		_gameObject = nullptr; // GameObject에 Add가 된 component이면 할당됨

};

