#pragma once

#include "CorePCH.h"
#include "Util.h"



class Message
{
public:

	Message();
	~Message();

	static Message* Create();

	void AddMessageWithKey( string key, void* message );

	void AddMessage( void* message );

	void* GetMessagePointerWithKey( string key, unsigned int count = 0 );

	void* GetMessagePointer( unsigned int count = 0 );

private:

	void Init();

private:

	map<string, vector<void*>>	_mapDataPointer;

	vector<void*> _vecDataPointer;

};

