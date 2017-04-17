#include "Plane.h"
#include "Resources.h"

Plane::Plane()
{
	_rigid = new RigidBody();
}

Plane::~Plane()
{
	SAFE_DELETE( _rigid );
}

void Plane::Start()
{
	///*--- Create 3D Model ---*/
	_modeling = ObjMeshObject::Create( OBJ_GROUND );
	_modeling->LoadTexture( TEX_GROUND );
	_modeling->GetMatrix()->SetPosition( 0, -17, 0 );
	_modeling->GetMatrix()->SetScale( 10, 1, 10 );
	MeshManager::Get()->AddMesh( _modeling );

	/*--- Collision ---*/
	// transform
	btTransform groundTrans;
	groundTrans.setIdentity();
	groundTrans.setOrigin( btVector3( 0, -10, 0 ) );

	//btTransform rotation;
	//btQuaternion q( btVector3( 1.0f, 0.0f, 0.0f ), -3.141592f*0.1f );
	//rotation.setIdentity();
	//rotation.setRotation( q );

	btTransform body = groundTrans; // *rotation;

	// create collision shape
	btCollisionShape* colShape = new btStaticPlaneShape( btVector3( 0, 1, 0 ), 1 );
	_rigid->SetCollisionShape( colShape );

	// create rigidbody
	colShape->calculateLocalInertia( 1, btVector3( 0, 0, 0 ) );

	_rigid->SetProperty( 0, 0.5f, 0, 0 );
	_rigid->CreateMotionState( body );

	auto rigidBodyCI = _rigid->CreateRigidbodyConstructionInfo();
	_rigid->CreateRigidBody( rigidBodyCI );
}

void Plane::Update()
{

}
