#pragma once

#include <btBulletDynamicsCommon.h>

class RigidBody
{
private:

	// Rigidbody의 속성
	struct Property
	{
		btScalar _restitution;		// 복원력, 탄성계수 (Restitution)
		btScalar _friction;			// 마찰력 (Friction)
		btScalar _linearDamping;	// 저항력 (Damping)
		btScalar _angluarDamping;

		Property() : _restitution( 0.5f ), _friction( 0.5f ), _linearDamping( 0 ), _angluarDamping( 0 )
		{

		}

		Property( btScalar restitution, btScalar friction, btScalar linearDamping, btScalar angluarDamping )
		{
			_restitution = restitution;
			_friction = friction;
			_linearDamping = linearDamping;
			_angluarDamping = angluarDamping;
		}

		~Property()
		{

		}
	};


public:
	RigidBody();
	~RigidBody();

	btRigidBody* GetRigidBody()
	{
		return _rigidBody;
	}

	// Create rigidbody with rigidbody construction infomation
	void CreateRigidBody( btRigidBody::btRigidBodyConstructionInfo& rigidBodyCI );

	// Create rigidbody setting rigidbody construction infomation within
	void CreateRigidBody( const btScalar mass = 0,
						  const btVector3& inertia = btVector3( 0, 0, 0 ) );

	void SetCollisionShape( btCollisionShape* colShape );

	void CreateMotionState( const btTransform& transform = btTransform() );

	// inertia = 관성
	btRigidBody::btRigidBodyConstructionInfo CreateRigidbodyConstructionInfo( const btScalar mass = 0,
																			  const btVector3& inertia = btVector3( 0, 0, 0 ) ) const;
	

	Property GetProperty() { return _property; }

	void SetProperty( btScalar restitution, btScalar friction, btScalar linearDamping, btScalar angularDamping )
	{
		_property._restitution = restitution;
		_property._friction = friction;
		_property._linearDamping = linearDamping;
		_property._angluarDamping = angularDamping;
	}
	
	// 복원력, 탄성계수 (Restitution)
	void SetRestitution( btScalar value )
	{
		_property._restitution = value;
	}

	// 마찰력 (Friction)
	void SetFriction( btScalar value )
	{
		_property._friction = value;
	}

	// 저항력 (Damping)
	void SetLinearDamping( btScalar value )
	{
		_property._linearDamping = value;
	}

	void SetAngluarDamping( btScalar value )
	{
		_property._angluarDamping = value;
	}

private:

	btCollisionShape* _colShape;
	btRigidBody* _rigidBody;
	btDefaultMotionState* _motionState;

	Property _property;
};

