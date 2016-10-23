#include "RigidBody.h"
#include "DynamicWorld.h"

RigidBody::RigidBody() : _rigidBody( nullptr ), _colShape( nullptr )
{

}


RigidBody::~RigidBody()
{
	DynamicWorld::Get()->GetDynamicWorld()->removeRigidBody( _rigidBody );

	delete(_rigidBody->getMotionState());

	SAFE_DELETE( _rigidBody );
	SAFE_DELETE( _colShape );
}


void RigidBody::CreateRigidBody( btDefaultMotionState* motionState, btRigidBody::btRigidBodyConstructionInfo& rigidBodyCI )
{
	_rigidBody = new btRigidBody( rigidBodyCI );

	DynamicWorld::Get()->GetDynamicWorld()->addRigidBody( _rigidBody );
}


void RigidBody::CreateRigidBody( btDefaultMotionState* motionState,
								 const btScalar mass,
								 const btVector3& inertia )
{
	btRigidBody::btRigidBodyConstructionInfo rigidBodyCI( mass, motionState, _colShape, inertia );

	rigidBodyCI.m_restitution = _property._restitution;
	rigidBodyCI.m_friction = _property._friction;
	rigidBodyCI.m_linearDamping = _property._linearDamping;
	rigidBodyCI.m_angularDamping = _property._angluarDamping;

	_rigidBody = new btRigidBody( rigidBodyCI );

	DynamicWorld::Get()->GetDynamicWorld()->addRigidBody( _rigidBody );
}


void RigidBody::SetCollisionShape( btCollisionShape* colShape )
{
	_colShape = colShape;
}


btDefaultMotionState* RigidBody::CreateMotionState( const btTransform& transform ) const
{
	btDefaultMotionState* motionState;

	if (transform == btTransform())
	{
		motionState = new btDefaultMotionState( btTransform( btQuaternion( 0, 0, 0, 1 ), btVector3( 0, 50, 0 ) ) );
	}

	else
	{
		motionState = new btDefaultMotionState( transform );
	}

	return motionState;
}


btRigidBody::btRigidBodyConstructionInfo RigidBody::CreateRigidbodyConstructionInfo( btDefaultMotionState* motionState,
																					 const btScalar mass,
																					 const btVector3& inertia ) const
{
	btRigidBody::btRigidBodyConstructionInfo rigidBodyCI( mass, motionState, _colShape, inertia );

	rigidBodyCI.m_restitution = _property._restitution;
	rigidBodyCI.m_friction = _property._friction;
	rigidBodyCI.m_linearDamping = _property._linearDamping;
	rigidBodyCI.m_angularDamping = _property._angluarDamping;

	return rigidBodyCI;
}

