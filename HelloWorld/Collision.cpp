#include "Collision.h"


Collision::Collision()
{
	//_fallRigid = new RigidBody();
	//_planeRigid = new RigidBody();
}

Collision::~Collision()
{
	//SAFE_DELETE( _planeRigid );
	//SAFE_DELETE( _fallRigid );
}

void Collision::Init()
{
	///*--- ¶¥ °´Ã¼ÀÇ Ãæµ¹Ã¼ ---*/
	//btCollisionShape* colShape = new btStaticPlaneShape( btVector3( 1, 0.5f, 0 ), 1 );
	//_planeRigid->SetCollisionShape( colShape );

	//auto motionState = _planeRigid->CreateMotionState();
	//auto rigidBodyCI = _planeRigid->CreateRigidbodyConstructionInfo( motionState );

	//_planeRigid->CreateRigidBody( motionState, rigidBodyCI );

	///*--- ¶³¾îÁö´Â °´Ã¼ÀÇ Ãæµ¹Ã¼ ---*/
	//btCollisionShape* fallColShape = new btBoxShape( btVector3( 10, 10, 10 ) );
	//_fallRigid->SetCollisionShape( fallColShape );

	//auto fallMotionState = _fallRigid->CreateMotionState();
	//auto fallRigidBodyCI = _fallRigid->CreateRigidbodyConstructionInfo( fallMotionState, 0.1f );

	//_fallRigid->CreateRigidBody( fallMotionState, fallRigidBodyCI );
}

void Collision::SimulateGravity( function<void( float )> func, RigidBody* rigidbody )
{
	if (_i < 300)
	{
		btTransform trans;
		rigidbody->GetRigidBody()->getMotionState()->getWorldTransform( trans );

		float y = trans.getOrigin().getY();
		func( y );

		_i++;

		//Message* msg = Message::Create();
		//msg->AddMessageWithKey( "y", &y );
		//MessageDispatcher::Get()->SendMessage( COLLISION_TEST, msg );
	}
}