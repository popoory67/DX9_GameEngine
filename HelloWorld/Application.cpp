#include "Application.h"

#include "InputHeader.h"
#include "GameObjectHeader.h"

// hello world
#include "Resources.h"
#include "KeyController.h"
#include "Collision.h"



GameManager::GameManager()
{

}

GameManager::~GameManager()
{

}


void GameManager::Start()
{
	// x mesh
	//for (int i = 0; i < 50; i++)
	//{
	//	XMeshPtr object( XMeshObject::Create( X_BOY ) );
	//	object->LoadTexture( TEX_BOY );
	//	object->GetMatrix()->Scale( 0.05f, 0.05f, 0.05f );
	//	object->GetShader()->LoadShader( DEFAULT_SHADER );
	//	//object->GetMatrix()->Rotate();
	//	MeshManager::Get().AddMesh( object );
	//}

	//for (int i = 0; i < 50; i++)
	//{
	//XMeshPtr tiger( XMeshObject::Create( X_TIGER ) );
	////tiger->LoadModel( X_TIGER );
	//tiger->LoadTexture( TEX_TIGER );
	//tiger->GetMatrix()->Scale( 10, 10, 10 );
	//tiger->GetMatrix()->Position( 10, 10, 10 );
	//tiger->GetShader()->LoadShader( DEFAULT_SHADER );
	//MeshManager::Get()->AddMesh( tiger );
	////}

	// obj mesh
	//ObjMeshObjectPtr ironMan(ObjMeshObject::Create(OBJ_IRON));
	//ironMan->GetMatrix()->Scale(0.15f, 0.15f, 0.15f);
	//ironMan->GetMatrix()->Position(11, -20, -1);
	//ironMan->GetMatrix()->Rotate(0, 10, 0);
	////ironMan->LoadTexture(TEX_DEFAULT);
	//ironMan->GetShader()->LoadShader(DEFAULT_SHADER);
	//MeshManager::Get().AddMesh(ironMan);
	
		//for (int i = 0; i < 10; i++)
		//{
	//ObjMeshPtr bb8( ObjMeshObject::Create( OBJ_BB8 ) );
	//bb8->GetMatrix()->Scale( 0.1f, 0.1f, 0.1f );
	//bb8->GetMatrix()->Position( -0, -0, 0 );
	//bb8->LoadTexture( TEX_BB8 );
	////bb8->GetShader()->LoadShader( DEFAULT_SHADER );
	//MeshManager::Get()->AddMesh( bb8 );
	//	//}

	//warrior = XSkinnedMesh::Create( X_WARRIOR );
	//warrior->LoadTexture( TEX_WARRIOR );
	//warrior->GetMatrix()->Scale( 0.5f, 0.5f, 0.5f );
	//warrior->GetMatrix()->Rotate( 90, 90, 90 );
	//warrior->GetMatrix()->Position( -0, 0, -50 );
	//warrior->SetAnimation( 2, 0 );
	//warrior->SetPose( 0.0001 );
	//MeshManager::Get()->AddMesh( warrior );

	//ObjMeshObjectPtr pot( ObjMeshObject::Create( OBJ_POT ) );
	//pot->GetMatrix()->Scale( 5, 5, 5 );
	//pot->GetMatrix()->Position( -10.0f, 0.0f, -10.0f );
	//MeshManager::Get().AddMesh( pot );

	//shared_ptr<GameObject> con(new KeyController());
	//shared_ptr<GameObject> col(new Collision());

	//AddComponent(con.get());
	//AddComponent(col.get());

	//GetComponent<Collision>().test();
}

void GameManager::Update()
{
	KeyInput();
}

void GameManager::KeyInput()
{
	/*if (KEY_INPUT.IsKeyDown( VK_F1 ))
	{
		GET_MESH( 2 )->GetMatrix()->Position( 0, 0, -10 );
	}

	if (KEY_INPUT.IsKeyDown( VK_UP ))
	{
		CameraManager::Get()->GetCamera( 0 )->SetPosition( 0, 0.05f, 0 );
	}

	if (KEY_INPUT.IsKeyDown( VK_DOWN ))
	{
		CameraManager::Get()->GetCamera( 0 )->SetPosition( 0, -0.05f, -0 );
	}

	if (KEY_INPUT.IsKeyDown( VK_RIGHT ))
	{
		CameraManager::Get()->GetCamera( 0 )->SetPosition( 0.05f, 0, 0 );
	}

	if (KEY_INPUT.IsKeyDown( VK_LEFT ))
	{
		CameraManager::Get()->GetCamera( 0 )->SetPosition( -0.05f, 0, 0 );
	}*/
}

void GameManager::Release()
{

}