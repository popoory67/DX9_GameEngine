#include "TestBehaviour.h"
#include "Util.h"
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
	_gameObject = GetGameObject();

	_gameObject->GetComponent<MeshModel>()->GetMatrix()->SetPosition(10, 0, 0);
}

void TestBehaviour::Update()
{
	if (KEY_INPUT.IsKeyDown(VK_SPACE))
	{
		_gameObject->GetComponent<MeshModel>()->GetMatrix()->SetPosition(10 + _test, 0, 0);
		_test += 0.1f;

		KEY_INPUT.KeyUp(VK_SPACE);
	}

}

void TestBehaviour::Release()
{

}