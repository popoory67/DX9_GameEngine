#pragma once

#include "CorePCH.h"

class Message;

using FuncVoid		= function< void() >;			// The function that receives the void argument
using FuncMessage	= function< void(Message*) >;	// The function that receives the message argument

using VObservers	= map< string, vector< FuncVoid > >;		// Void observers
using MObservers	= map< string, vector< FuncMessage > >;		// Message observers

class Object
{

public:
	Object();
	virtual ~Object();

	static void		Destroy(Object* object);
};

