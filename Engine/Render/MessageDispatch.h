#pragma once


class Message;		// pointer�θ� ���Ǳ� ������ include ��� ���� ����

typedef function< void() >						FuncVoid;
typedef function< void(Message*) >				FuncMessage;
typedef map< string, vector< FuncVoid > >		MessageVectorFuncVoid;
typedef map< string, vector< FuncMessage > >	MessageVectorFuncMessage;


class MessageDispatch
{
public:

	~MessageDispatch();

	static MessageDispatch& Get();

	void AddObserver(string key, FuncVoid func);
	void AddObserver(string key, FuncMessage func);

	void SendMessageWithKey(string key);
	void SendMessageWithKey(string key, Message* message);

private:

	MessageDispatch();

private:

	static MessageDispatch*		_instance;

	MessageVectorFuncVoid		_messageVectorV;
	MessageVectorFuncMessage	_messageVectorM;

};

