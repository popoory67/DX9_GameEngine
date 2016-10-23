#include "Application.h"
#include "BehaviourManager.h"
#include "CollisionShapeRenderer.h"

// hello world
#include "Resources.h"
#include "KeyController.h"
#include "Collision.h"


MyGameManager::MyGameManager() : _x( 0 ), _y( 0 ), _z( 0 )
{
	_col = new Collision();

	_fallRigid = new RigidBody();
	_fallRigid2 = new RigidBody();
	_planeRigid = new RigidBody();
}

MyGameManager::~MyGameManager()
{
	delete(_col);

	SAFE_DELETE( _planeRigid );
	SAFE_DELETE( _fallRigid );
	SAFE_DELETE( _fallRigid2 );
}


void MyGameManager::Start()
{
	/*------- x mesh --------*/

	_object = XMeshObject::Create( X_BOY );
	_object->LoadTexture( TEX_BOY );
	_object->GetMatrix()->SetScale( 0.1f, 0.1f, 0.1f );
	_object->GetMatrix()->SetPosition( -10, 0, 0 );
	_object->GetShader()->LoadShader( DEFAULT_SHADER );
	//object->GetMatrix()->Rotate();
	MeshManager::Get()->AddMesh( _object );

	_warrior = XSkinnedMesh::Create( X_WARRIOR );
	_warrior->LoadTexture( TEX_WARRIOR );
	_warrior->GetMatrix()->SetScale( 0.5f, 0.5f, 0.5f );
	_warrior->GetMatrix()->SetRotate( 90, 90, 90 );
	_warrior->GetMatrix()->SetPosition( 40, 20, -5 );
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
	//_bb8 = ObjMeshObject::Create( OBJ_BB8 );
	//_bb8->GetMatrix()->Scale( 0.1f, 0.1f, 0.1f );
	//_bb8->GetMatrix()->Position( -0, -0, 0 );
	//_bb8->LoadTexture( TEX_BB8 );
	//_bb8->GetShader()->LoadShader( DEFAULT_SHADER );
	//MeshManager::Get()->AddMesh( _bb8 );
	//	//}

	//ObjMeshObjectPtr pot( ObjMeshObject::Create( OBJ_POT ) );
	//pot->GetMatrix()->Scale( 5, 5, 5 );
	//pot->GetMatrix()->Position( -10.0f, 0.0f, -10.0f );
	//MeshManager::Get().AddMesh( pot );

	/*------- Component test --------*/

	Component* keyController( new KeyController() );
	AddComponent( keyController );
	
	/*------- Collision test --------*/

	_col->Init();

	/*--- 땅 객체의 충돌체 ---*/
	btTransform groundTrans;
	groundTrans.setIdentity();
	groundTrans.setOrigin( btVector3( 0, -20, 0 ) );
	//btQuaternion quat( btVector3( 1, 1, 1 ), 1 );
	//groundTrans.setRotation( quat );

	btCollisionShape* colShape = new btStaticPlaneShape( btVector3( 0, 1, 0 ), 1 );
	_planeRigid->SetCollisionShape( colShape );

	auto motionState = _planeRigid->CreateMotionState( groundTrans );
	auto rigidBodyCI = _planeRigid->CreateRigidbodyConstructionInfo( motionState );

	_planeRigid->CreateRigidBody( motionState, rigidBodyCI );

	/*--- 떨어지는 객체의 충돌체 ---*/
	btCollisionShape* fallColShape = new btBoxShape( btVector3( 10, 10, 10 ) ); //new btSphereShape( 20 ); // new btCapsuleShape( 10, 10 );
	_fallRigid->SetCollisionShape( fallColShape );
	fallColShape->calculateLocalInertia( 1, btVector3( 0, 0, 0 ) );

	btTransform trans;
	trans.setIdentity();
	trans.setOrigin( btVector3( 5, 0, 0 ) );

	auto fallMotionState = _fallRigid->CreateMotionState( trans );
	auto fallRigidBodyCI = _fallRigid->CreateRigidbodyConstructionInfo( fallMotionState, 1 );

	_fallRigid->CreateRigidBody( fallMotionState, fallRigidBodyCI );

	// wire frame test
	CollisionWireFrame* _wire = new CollisionWireFrame();
	_wire->_rigidBody = _fallRigid->GetRigidBody();
	CollisionShapeRenderer::Get()->AddWireFrame( _wire );

	/*--- 떨어지는 객체의 충돌체2 ---*/
	btTransform trans2;
	trans2.setIdentity();
	trans2.setOrigin( btVector3( -0, 5, 0 ) );

	btCollisionShape* fallColShape2 = new btSphereShape( 10 ); //new btBoxShape( btVector3( 100, 100, 10 ) );
	_fallRigid2->SetCollisionShape( fallColShape2 );
	fallColShape2->calculateLocalInertia( 1, btVector3( 0, 0, 0 ) );

	auto fallMotionState2 = _fallRigid2->CreateMotionState( trans2 );
	auto fallRigidBodyCI2 = _fallRigid2->CreateRigidbodyConstructionInfo( fallMotionState2, 1 );

	_fallRigid2->CreateRigidBody( fallMotionState2, fallRigidBodyCI2 );
}

void MyGameManager::Update()
{
	// 화살표 키를 이용하여 카메라 조작
	GetComponent<KeyController>().KeyInput();

	DynamicWorld::Get()->GetDynamicWorld()->stepSimulation( 1 / 60.f, 10 );

	btTransform t;
	_fallRigid->GetRigidBody()->getMotionState()->getWorldTransform( t );
	auto test = t.getRotation().getAngle();
	//_fallRigid->SetRestitution( 1 );
	_object->GetMatrix()->SetPosition( t.getOrigin().getX(), t.getOrigin().getY(), t.getOrigin().getZ() );
	_object->GetMatrix()->SetRotate( t.getRotation().getAngle(), t.getRotation().getAngle(), t.getRotation().getAngle() );

	btTransform t2;
	_fallRigid2->GetRigidBody()->getMotionState()->getWorldTransform( t2 );

	_warrior->GetMatrix()->SetPosition( t2.getOrigin().getX(), t2.getOrigin().getY(), t2.getOrigin().getZ() );
	_warrior->GetMatrix()->SetRotate( t2.getRotation().getAngle(), t2.getRotation().getAngle(), t2.getRotation().getAngle() );

	// 애니메이션 테스트
	_warrior->SetAnimation( 2, 0 );
	_warrior->SetPose( 0.00001f );
}

void MyGameManager::Release()
{

}