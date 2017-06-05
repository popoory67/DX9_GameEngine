#include "TestScene.h"
#include "SceneManager.h"


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

	// Add scene
	SceneManager::Get().AddScene( *ret );

	return ret;
}

void TestScene::Init()
{
	for (int i = 0; i < 5; i++)
	{
		_gameObject[i] = new TestGameObject();
		/*_child[i] = new TestGameObject();

		_gameObject[i]->AddChild(_child[i]);*/

		Scene::AddRootGameObject(_gameObject[i]); // Add a root game object to this scene
	}
}