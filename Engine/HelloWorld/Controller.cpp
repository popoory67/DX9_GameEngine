#include "Controller.h"
#include "MessageHeader.h"

Controller::Controller()
{
	//_game = new GameManager();
}


Controller::~Controller()
{
}


void Controller::Init()
{
	//function<void(Message*)> func = tr1::bind(&GameManager::Start, this/*, placeholders::_1*/);	// Start �Լ��� �μ��� ����

	//MessageDispatcher::Get().AddObserver("Start", func);
}

void Controller::Update()
{
	//Message* msg = Message::Create();

	//msg->AddMessageWithKey("Start", _game->Start);

	//MessageDispatcher::Get().SendMessage("Start", msg);
}