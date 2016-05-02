#include "Application.h"

#include "Resources.h"
#include "RenderHeader.h"


GameManager::GameManager()
{

}

GameManager::~GameManager()
{

}


void GameManager::Start()
{
	// mesh
	SHARED_PTR(MeshObject) object(new MeshObject());

	object->LoadModel(BODY);
	object->LoadTexture(TEXTURE);
	object->GetMatrix()->Scale(0.05f, 0.05f, 0.05f);

	Renderer::Get().AddMesh(object);

	SHARED_PTR(MeshObject) tiger(new MeshObject());

	tiger->LoadModel(TIGER);
	tiger->LoadTexture(TEXTURE2);
	tiger->GetMatrix()->Scale(10, 10, 10);
	tiger->GetMatrix()->Position(10, 10, 10);

	Renderer::Get().AddMesh(tiger);
}

void GameManager::Update()
{

}

void GameManager::Release()
{

}