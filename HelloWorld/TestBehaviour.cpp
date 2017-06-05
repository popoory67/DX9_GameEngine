#include "TestBehaviour.h"
#include "Util.h"
#include "TestGameObject.h"

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

}

void TestBehaviour::Release()
{

}