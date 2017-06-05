#include "TestGameObject.h"
#include "Resources.h"


TestGameObject::TestGameObject()
{
	_mesh = new MeshRenderer();
}

TestGameObject::~TestGameObject()
{
	SAFE_DELETE(_mesh);
}

void TestGameObject::Init()
{	
	auto model = _mesh->Create(X_BOY, TEX_BOY);

	model->GetMatrix()->SetPosition(0, 0, 0);
	model->GetMatrix()->SetScale(0.1f, 0.1f, 0.1f);

	// Add a game behaviour
	AddComponent(&_testBehaviour);

	auto test = GetComponent<TestBehaviour>();
}