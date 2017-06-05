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
}

void TestGameObject::Init()
{	
	auto model = _meshRenderer->Create(X_BOY, TEX_BOY);
	
	model->GetMatrix()->SetPosition(0, 0, 0);
	model->GetMatrix()->SetScale(0.1f, 0.1f, 0.1f);

	// Add a game behaviour
	AddComponent(model);
	AddComponent(_testBehaviour);

}