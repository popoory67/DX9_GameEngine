#include "Application.h"

#include "Resources.h"

#include "D3D9Header.h"
#include "D3D11Header.h"


GameManager::GameManager()
{
	
}

GameManager::~GameManager()
{

}


void GameManager::Start()
{
	// x mesh
	SHARED_PTR(XMeshObject) object(new XMeshObject());

	object->LoadModel(BODY);
	object->LoadTexture(TEXTURE);
	object->GetMatrix()->Scale(0.05f, 0.05f, 0.05f);
	//object->GetMatrix()->Rotate();

	Renderer::Get().AddMesh(object);

	SHARED_PTR(XMeshObject) tiger(new XMeshObject());

	tiger->LoadModel(TIGER);
	tiger->LoadTexture(TEXTURE2);
	tiger->GetMatrix()->Scale(10, 10, 10);
	tiger->GetMatrix()->Position(10, 10, 10);

	Renderer::Get().AddMesh(tiger);

	// obj mesh
	ObjMeshObject* mesh = ObjMeshObject::Create(OBJ_TEST);
	Renderer::Get().AddMesh(mesh);
}

void GameManager::Update()
{

}

void GameManager::Release()
{

}