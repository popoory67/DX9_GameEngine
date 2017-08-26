#include "TestBehaviour.h"
#include "TestGameObject.h"
#include "KeyInput.h"

TestBehaviour::TestBehaviour()
{
}

TestBehaviour::~TestBehaviour()
{

}


void TestBehaviour::Start()
{
	GameBehaviour::Start();

	_gameObject->GetComponent<MeshModel>()->GetMatrix()->SetPosition(10, 0, 0);
	_gameObject->GetComponent<MeshModel>()->GetMatrix()->SetScale(0.1f, 0.1f, 0.1f);

	auto func = [&]() 
	{
		_gameObject->GetComponent<MeshModel>()->GetMatrix()->SetPosition(10 + _test, 0, 0);
		_test += 0.01f;
		//Util::PutLogMessage("x move");
	};

	auto func2 = [&]()
	{
		_gameObject->GetComponent<MeshModel>()->GetMatrix()->SetPosition(0, 10 + _test2, 0);
		_test2 += 0.01f;
		//Util::PutLogMessage("y move");
	};

	_gameObject->AddObserver("hello", func);
	_gameObject->AddObserver("hello", func2);
}

void TestBehaviour::Update()
{
	//if (KEY_INPUT.IsKeyDown(VK_SPACE))
	//{
	//	_gameObject->GetComponent<MeshModel>()->GetMatrix()->SetPosition(10 + _test, 0, 0);
	//	_test += 0.1f;

	//	KEY_INPUT.KeyUp(VK_SPACE);
	//}

	_gameObject->SendMessageToObservers("hello");
}

void TestBehaviour::Release()
{
	
}