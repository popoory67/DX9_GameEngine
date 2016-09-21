#include "Application.h"
#include "InputHeader.h"
#include "GameObjectHeader.h"

// hello world
#include "Resources.h"
#include "KeyController.h"
#include "Collision.h"


GameManager::GameManager() : x( 0 ), y( 0 ), z( 0 )
{

}

GameManager::~GameManager()
{

}


void GameManager::Start()
{
	/*------- x mesh --------*/

	_object = XMeshObject::Create( X_BOY );
	_object->LoadTexture( TEX_BOY );
	_object->GetMatrix()->Scale( 0.1f, 0.1f, 0.1f );
	_object->GetShader()->LoadShader( DEFAULT_SHADER );
	//object->GetMatrix()->Rotate();
	MeshManager::Get()->AddMesh( _object );

	_warrior = XSkinnedMesh::Create( X_WARRIOR );
	_warrior->LoadTexture( TEX_WARRIOR );
	_warrior->GetMatrix()->Scale( 0.5f, 0.5f, 0.5f );
	_warrior->GetMatrix()->Rotate( 90, 90, 90 );
	_warrior->GetMatrix()->Position( -0, 0, -50 );
	MeshManager::Get()->AddMesh( _warrior );

	/*------- obj mesh --------*/

	//ObjMeshPtr ironMan( ObjMeshObject::Create( OBJ_IRON ) );
	//ironMan->GetMatrix()->Scale(0.15f, 0.15f, 0.15f);
	//ironMan->GetMatrix()->Position(11, -20, -1);
	//ironMan->GetMatrix()->Rotate(0, 10, 0);
	////ironMan->LoadTexture(TEX_DEFAULT);
	//ironMan->GetShader()->LoadShader(DEFAULT_SHADER);
	//MeshManager::Get()->AddMesh(ironMan);

	//for (int i = 0; i < 10; i++)
	//{
	//ObjMeshPtr bb8( ObjMeshObject::Create( OBJ_BB8 ) );
	//bb8->GetMatrix()->Scale( 0.1f, 0.1f, 0.1f );
	//bb8->GetMatrix()->Position( -0, -0, 0 );
	//bb8->LoadTexture( TEX_BB8 );
	//bb8->GetShader()->LoadShader( DEFAULT_SHADER );
	//MeshManager::Get()->AddMesh( bb8 );
	//	//}

	//ObjMeshObjectPtr pot( ObjMeshObject::Create( OBJ_POT ) );
	//pot->GetMatrix()->Scale( 5, 5, 5 );
	//pot->GetMatrix()->Position( -10.0f, 0.0f, -10.0f );
	//MeshManager::Get().AddMesh( pot );

	/*------- Component test --------*/

	//shared_ptr<GameObject> con(new KeyController());
	//shared_ptr<GameObject> col(new Collision());

	//AddComponent(con.get());
	//AddComponent(col.get());

	//GetComponent<Collision>().test();
}

void GameManager::Update()
{
	// 화살표 키를 이용하여 카메라 조작
	KeyInput();

	// 모델링의 좌표 변화 테스트
	x += 0.01f;
	_object->GetMatrix()->Position( x, y, z );

	// 애니메이션 테스트
	_warrior->SetAnimation( 2, 0 );
	_warrior->SetPose( 0.00001 );
}

void GameManager::KeyInput()
{
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
	}
}

void GameManager::Release()
{

}