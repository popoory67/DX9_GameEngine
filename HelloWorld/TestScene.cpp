#include "TestScene.h"
#include "SceneManager.h"
#include "Resources.h"

#include "TestCustomComponent.h"

TestScene::TestScene()
{
	
}

TestScene::~TestScene()
{
	
}

TestScene* TestScene::Create()
{
	// Create test scene
	TestScene* ret = new TestScene();
	ret->Init();

	// Create test root game object
	GameObject* testGameObject = new GameObject();
	ret->AddRootGameObject(testGameObject);

	// Create test game behaviour
	TestCustomComponent* testComponent = new TestCustomComponent();

	// Add game behaviour
	testGameObject->AddComponent(testComponent);

	// Add scene
	SceneManager::Get().AddScene( ret );

	return ret;
}
