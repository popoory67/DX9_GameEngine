#pragma once


class Message;		// pointer로만 사용되기 때문에 include 대신 전방 선언

typedef function< void() >						FuncVoid;
typedef function< void(Message*) >				FuncMessage;
typedef map< string, vector< FuncVoid > >		MessageVectorFuncVoid;
typedef map< string, vector< FuncMessage > >	MessageVectorFuncMessage;


class MessageDispatcher
{
public:

	~MessageDispatcher();

	static MessageDispatcher& Get();

	// 메시지 클래스에서 메시지를 가져온 후에 호출
	void AddObserver(string key, FuncVoid func);
	void AddObserver(string key, FuncMessage func);

	// 가장 마지막에 호출
	void SendMessage(string key);
	void SendMessage(string key, Message* message);

private:

	MessageDispatcher();

private:

	static MessageDispatcher*	_instance;

	MessageVectorFuncVoid		_messageVectorV;
	MessageVectorFuncMessage	_messageVectorM;

};

