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
	ObjMeshObjectPtr mesh2 = ObjMeshObject::Create(OBJ_TEST);
	mesh2->GetMatrix()->Scale(0.1f, 0.1f, 0.1f);
	mesh2->GetMatrix()->Position(-10, -5, 0);
	mesh2->LoadTexture(TEXTURE_DEFAULT);
	mesh2->GetShader()->LoadShader(DEFAULT_SHADER);
	Renderer::Get().AddMesh(mesh2);

	// x mesh
	XMeshObjectPtr object(new XMeshObject());
	object->LoadModel(BODY);
	object->LoadTexture(TEXTURE);
	object->GetMatrix()->Scale(0.05f, 0.05f, 0.05f);
	object->GetShader()->LoadShader(DEFAULT_SHADER);
	//object->GetMatrix()->Rotate();
	Renderer::Get().AddMesh(object); // 자료구조에 추가

	//XMeshObjectPtr tiger(new XMeshObject());
	//tiger->LoadModel(TIGER);
	//tiger->LoadTexture(TEXTURE2);
	//tiger->GetMatrix()->Scale(10, 10, 10);
	//tiger->GetMatrix()->Position(10, 10, 10);
	//tiger->GetShader()->LoadShader(DEFAULT_SHADER);
	//Renderer::Get().AddMesh(tiger);

	// obj mesh
	//ObjMeshObjectPtr mesh = ObjMeshObject::Create(OBJ_IRON);
	//mesh->GetMatrix()->Scale(0.1f, 0.1f, 0.1f);
	//mesh->GetMatrix()->Position(-10, -10, -10);
	//mesh->GetShader()->LoadShader(DEFAULT_SHADER);
	//Renderer::Get().AddMesh(mesh);

	//ObjMeshObjectPtr mesh2 = ObjMeshObject::Create(OBJ_TEST);
	//mesh2->GetMatrix()->Scale(0.1f, 0.1f, 0.1f);
	//mesh2->GetMatrix()->Position(-10, -5, 0);
	//mesh2->GetShader()->LoadShader(DEFAULT_SHADER);
	//Renderer::Get().AddMesh(mesh2);
}

void GameManager::Update()
{

}

void GameManager::Release()
{

}