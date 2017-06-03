#include "TestGameObject.h"
#include "Resources.h"


TestGameObject::TestGameObject()
{
}

TestGameObject::~TestGameObject()
{
	SAFE_DELETE(_mesh);
}

void TestGameObject::Init()
{	
	_mesh = new MeshRenderer();
	_mesh->Create(X_BOY);

	// Add a game behaviour
	AddComponent(&_testBehaviour);
}