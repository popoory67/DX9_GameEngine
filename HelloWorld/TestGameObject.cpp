#include "TestGameObject.h"
#include "Resources.h"

TestGameObject::TestGameObject()
{
	_meshRenderer	= new MeshRenderer();
	_testBehaviour	= new TestBehaviour();
}

TestGameObject::~TestGameObject()
{
	SAFE_DELETE(_meshRenderer);
	SAFE_DELETE(_testBehaviour);
}

void TestGameObject::Init()
{	
	auto model = _meshRenderer->Create(X_BOY, TEX_BOY);

	// Add a game behaviour
	AddComponent(model);
	AddComponent(_testBehaviour);
}