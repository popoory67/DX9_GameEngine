#pragma once

class Message;

using FuncVoid		= function< void() >;			// �μ��� ���� �Լ���
using FuncMessage	= function< void( Message* ) >;	// �μ��� �޽����� �Լ���

class MessageDispatcher
{
	using MessageVectorFuncVoid		= map< string, vector< FuncVoid > >;
	using MessageVectorFuncMessage	= map< string, vector< FuncMessage > >;

public:

	~MessageDispatcher();

	static MessageDispatcher* Get();

	// �޽��� Ŭ�������� �޽����� ������ �Ŀ� ȣ��
	void AddObserver( string key, FuncVoid func );
	void AddObserver( string key, FuncMessage func );

	// ���� �������� ȣ��
	void SendMessage( string key );
	void SendMessage( string key, Message* message );

private:

	MessageDispatcher();

private:

	static MessageDispatcher*	_instance;

	MessageVectorFuncVoid		_messageVectorVoid;
	MessageVectorFuncMessage	_messageVectorMessage;

};

