#pragma once


class Message;		// pointer�θ� ���Ǳ� ������ include ��� ���� ����

typedef function< void() >						FuncVoid;
typedef function< void(Message*) >				FuncMessage;
typedef map< string, vector< FuncVoid > >		MessageVectorFuncVoid;
typedef map< string, vector< FuncMessage > >	MessageVectorFuncMessage;


class MessageDispatcher
{
public:

	~MessageDispatcher();

	static MessageDispatcher& Get();

	// �޽��� Ŭ�������� �޽����� ������ �Ŀ� ȣ��
	void AddObserver(string key, FuncVoid func);
	void AddObserver(string key, FuncMessage func);

	// ���� �������� ȣ��
	void SendMessage(string key);
	void SendMessage(string key, Message* message);

private:

	MessageDispatcher();

private:

	static MessageDispatcher*	_instance;

	MessageVectorFuncVoid		_messageVectorV;
	MessageVectorFuncMessage	_messageVectorM;

};

