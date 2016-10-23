#include "CorePCH.h"
#include "MessageDispatcher.h"


MessageDispatcher* MessageDispatcher::_instance = nullptr;

MessageDispatcher::MessageDispatcher()
{

}

MessageDispatcher::~MessageDispatcher()
{
	if (_instance)
	{
		SAFE_DELETE( _instance );
	}
}

MessageDispatcher* MessageDispatcher::Get()
{
	if (!_instance)
	{
		_instance = new MessageDispatcher();
	}

	return _instance;
}

void MessageDispatcher::AddObserver( string key, FuncVoid func )
{
	_messageVectorVoid[key].push_back( func );
}

void MessageDispatcher::AddObserver( string key, FuncMessage func )
{
	_messageVectorMessage[key].push_back( func );
}

void MessageDispatcher::SendMessage( string key )
{
	SendMessage( key, NULL );
}

void MessageDispatcher::SendMessage( string key, Message* message )
{
	if (_messageVectorVoid.find( key ) != _messageVectorVoid.end())
	{
		for (auto i = 0; i < _messageVectorVoid[key].size(); i++)
		{
			_messageVectorVoid[key][i]();
		}
	}

	if (_messageVectorMessage.find( key ) != _messageVectorMessage.end())
	{
		for (auto i = 0; i < _messageVectorMessage[key].size(); i++)
		{
			_messageVectorMessage[key][i]( message );
		}
	}

	if (message)
	{
		delete (message);
	}
}