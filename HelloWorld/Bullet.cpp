#include "Bullet.h"
#include "CollisionShapeRenderer.h"
#include "CameraManager.h"

#include "Player.h"


//bool callbackFunc( btManifoldPoint& cp,
//				   const btCollisionObjectWrapper* colObj0Wrap, int partId0, int index0,
//				   const btCollisionObjectWrapper* colObj1Wrap, int partId1, int index1 )
//{
//	gHit = true;
//
//	return false;
//}

Bullet::Bullet()
{
	_rigid = new RigidBody();
}

Bullet::~Bullet()
{
	SAFE_DELETE( _rigid );
}

void Bullet::CreateBullet()
{
	//gContactAddedCallback = callbackFunc;

	auto cam = CameraManager::Get()->GetCamera( 0 )->GetCameraVector();
	auto eye = cam->_eyeVec;

	/*--- Collision ---*/
	btTransform t;
	t.setIdentity();
	t.setOrigin( btVector3( eye.x, eye.y, eye.z ) );

	// create collision shape
	btCollisionShape* colShape = new btSphereShape( 1 ); //new btCapsuleShape( 10, 10 );
	_rigid->SetCollisionShape( colShape );
	_rigid->SetProperty( 0, 0.5f, 0, 0 );
	colShape->calculateLocalInertia( 1, btVector3( 0, 0, 0 ) );

	// create rigidbody
	_rigid->CreateMotionState( t );
	auto rigidBodyCI = _rigid->CreateRigidbodyConstructionInfo( 1 );
	_rigid->CreateRigidBody( rigidBodyCI );

	auto look = cam->_lookVec - cam->_eyeVec;
	_rigid->GetRigidBody()->setLinearVelocity( btVector3( look.x, look.y, look.z ) );

	// add to wire frame renderer
	CollisionWireFrame* wire = new CollisionWireFrame( _rigid->GetRigidBody() );
	CollisionShapeRenderer::Get()->AddDynamicWireFrame( wire );
}

void Bullet::SetDetectionFlag()
{
	_rigid->GetRigidBody()->setCollisionFlags( _rigid->GetRigidBody()->getCollisionFlags()
											   | btCollisionObject::CF_CUSTOM_MATERIAL_CALLBACK );
}