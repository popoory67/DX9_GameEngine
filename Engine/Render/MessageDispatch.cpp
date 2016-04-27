#include "RenderPCH.h"
#include "MessageDispatch.h"


MessageDispatch* MessageDispatch::_instance = NULL;

MessageDispatch::MessageDispatch()
{

}

MessageDispatch::~MessageDispatch()
{
	if ( _instance ) delete (_instance);
}

MessageDispatch& MessageDispatch::Get()
{
	if ( !_instance )
	{
		_instance = new MessageDispatch();
	}

	return *_instance;
}

void MessageDispatch::AddObserver(string key, FuncVoid func)
{
	_messageVectorV[key].push_back(func);
}

void MessageDispatch::AddObserver(string key, FuncMessage func)
{
	_messageVectorM[key].push_back(func);
}

void MessageDispatch::SendMessageWithKey(string key)
{
	SendMessageWithKey(key, NULL);
}

void MessageDispatch::SendMessageWithKey(string key, Message* message)
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