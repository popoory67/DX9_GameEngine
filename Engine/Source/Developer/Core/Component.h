#pragma once

#include "Object.h"

class GameObject;
class Message;

using FuncVoid			= function< void() >;				// The function that receives the void argument
using FuncMessage		= function< void(Message*) >;		// The function that receives the message argument

using VObservers		= map< string, vector< FuncVoid > >;	// Void observers
using MObservers		= map< string, vector< FuncMessage > >;	// Message observers

/**
 * The component class is a prototype of all functions. 
 */
class Component : public Object
{

public:
	Component();
	virtual ~Component();

	void			SetGameObject(GameObject* gameObject) { _gameObject = gameObject; } // ���� ����, ���� ����
	GameObject*		GetGameObject() { return _gameObject; }

	// Returns the component of the current game object.
	template<class Type>
	Type& GetComponent()
	{
		if (!_gameObject)
			return nullptr;

		return _gameObject->GetComponent<Type>();
	}

	// Add observer that runs when a key calls.
	void			AddObserver(string key, FuncVoid func);
	void			AddObserver(string key, FuncMessage func);

	// Calls the methods mapped the key and message.
	void			SendMessageToObservers(string key);
	void			SendMessageToObservers(string key, Message* message);

protected:

	GameObject*		_gameObject = nullptr; // GameObject�� Add�� �� component�̸� �Ҵ��

private:

	VObservers*		_voidObservers;
	MObservers*		_msgObservers;

};

