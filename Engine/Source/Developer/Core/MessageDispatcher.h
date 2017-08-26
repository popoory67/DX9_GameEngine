#pragma once

class Message;

using FuncVoid		= function< void() >;			// 인수가 없는 함수형
using FuncMessage	= function< void( Message* ) >;	// 인수가 메시지인 함수형

class MessageDispatcher
{
	using MessageVectorFuncVoid		= map< string, vector< FuncVoid > >;
	using MessageVectorFuncMessage	= map< string, vector< FuncMessage > >;

public:

	~MessageDispatcher();

	static MessageDispatcher* Get();

	// 메시지 클래스에서 메시지를 가져온 후에 호출
	void AddObserver( string key, FuncVoid func );
	void AddObserver( string key, FuncMessage func );

	// 가장 마지막에 호출
	void SendMessage( string key );
	void SendMessage( string key, Message* message );

private:

	MessageDispatcher();

private:

	static MessageDispatcher*	_instance;

	MessageVectorFuncVoid		_messageVectorVoid;
	MessageVectorFuncMessage	_messageVectorMessage;

};

