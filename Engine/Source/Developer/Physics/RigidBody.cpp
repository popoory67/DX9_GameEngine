#include "RigidBody.h"
#include "DynamicWorld.h"

RigidBody::RigidBody() : _rigidBody( nullptr ), _colShape( nullptr )
{

}


RigidBody::~RigidBody()
{
	DynamicWorld::Get()->GetDynamicWorld()->removeRigidBody( _rigidBody );

	delete(_rigidBody->getMotionState());
	delete(_rigidBody->getCollisionShape());

	SAFE_DELETE( _rigidBody );
}

void RigidBody::CreateRigidBody( btRigidBody::btRigidBodyConstructionInfo& rigidBodyCI )
{
	_rigidBody = new btRigidBody( rigidBodyCI );

	DynamicWorld::Get()->GetDynamicWorld()->addRigidBody( _rigidBody );
}


void RigidBody::CreateRigidBody( const btScalar mass,
								 const btVector3& inertia )
{
	btRigidBody::btRigidBodyConstructionInfo rigidBodyCI( mass, _motionState, _colShape, inertia );

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


void RigidBody::CreateMotionState( const btTransform& transform )
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

	_motionState = motionState;
}

btRigidBody::btRigidBodyConstructionInfo RigidBody::CreateRigidbodyConstructionInfo( const btScalar mass,
																					 const btVector3& inertia ) const
{
	btRigidBody::btRigidBodyConstructionInfo rigidBodyCI( mass, _motionState, _colShape, inertia );

	rigidBodyCI.m_restitution = _property._restitution;
	rigidBodyCI.m_friction = _property._friction;
	rigidBodyCI.m_linearDamping = _property._linearDamping;
	rigidBodyCI.m_angularDamping = _property._angluarDamping;

	return rigidBodyCI;
}

