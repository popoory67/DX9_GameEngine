#include "CorePCH.h"
#include "Message.h"


Message::Message()
{
}


Message::~Message()
{
}


Message* Message::Create()
{
	Message* object = new Message();

	object->Init();

	return object;
}

void Message::Init()
{
	_mapDataPointer.clear();

	_vecDataPointer.clear();
}

void Message::AddMessageWithKey( string key, void* message )
{
	_mapDataPointer[key].push_back( message );
}


void Message::AddMessage( void* message )
{
	_vecDataPointer.push_back( message );
}


void* Message::GetMessagePointerWithKey( string key, unsigned int count/* = 0*/ )
{
	if (_mapDataPointer.find( key ) != _mapDataPointer.end())
	{
		if (_mapDataPointer[key].size() > count)
		{
			return _mapDataPointer[key][count];
		}
	}

	// assert
	assert( Util::ErrorMessage( "get message" ) );

	return NULL;
}


void* Message::GetMessagePointer( unsigned int count/* = 0*/ )
{
	if (_vecDataPointer.size() > count)
	{
		return _vecDataPointer[count];
	}

	// assert
	assert( Util::ErrorMessage( "get message" ) );

	return NULL;
}
