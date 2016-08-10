#include "CorePCH.h"
#include "MessageDispatcher.h"


MessageDispatcher* MessageDispatcher::_instance = nullptr;

MessageDispatcher::MessageDispatcher()
{

}

MessageDispatcher::~MessageDispatcher()
{
	if ( _instance ) delete (_instance);
}

MessageDispatcher& MessageDispatcher::Get()
{
	if ( !_instance )
	{
		_instance = new MessageDispatcher();
	}

	return *_instance;
}

void MessageDispatcher::AddObserver(string key, FuncVoid func)
{
	_messageVectorV[key].push_back(func);
}

void MessageDispatcher::AddObserver(string key, FuncMessage func)
{
	_messageVectorM[key].push_back(func);
}

void MessageDispatcher::SendMessage(string key)
{
	SendMessage(key, NULL);
}

void MessageDispatcher::SendMessage(string key, Message* message)
{
	if (_messageVectorV.find(key) != _messageVectorV.end())
	{
		for (auto i = 0; i < _messageVectorV[key].size(); i++)
		{
			_messageVectorV[key][i]();
		}
	}

	if (_messageVectorM.find(key) != _messageVectorM.end())
	{
		for (auto i = 0; i < _messageVectorM[key].size(); i++)
		{
			_messageVectorM[key][i](message);
		}
	}

	if ( message ) delete (message);
}