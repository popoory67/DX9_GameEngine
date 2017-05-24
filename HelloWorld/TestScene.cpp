#include "TestScene.h"
#include "SceneManager.h"

#include "TestGameObject.h"
#include "TestCustomComponent.h"

TestScene::TestScene()
{
	_rootGameObject = new GameObject();
}

TestScene::~TestScene()
{
	SAFE_DELETE(_rootGameObject);
}

TestScene* TestScene::Create()
{
	// Create test scene
	TestScene* ret = new TestScene();
	ret->Init();

	// Add scene
	SceneManager::Get().AddScene( ret );

	return ret;
}

void TestScene::Init()
{
	TestGameObject* gameObject = new TestGameObject();
	gameObject->Init();
	_rootGameObject = gameObject;

 	Scene::AddRootGameObject(_rootGameObject); // Add a root game object to this scene

	// Create a test game behaviour
	TestCustomComponent* testComponent = new TestCustomComponent();

	// Add a game behaviour
	_rootGameObject->AddComponent(testComponent);
}