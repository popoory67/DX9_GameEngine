#pragma once

#include <btBulletDynamicsCommon.h>

class RigidBody
{
private:

	// Rigidbody�� �Ӽ�
	struct Property
	{
		btScalar _restitution;		// ������, ź����� (Restitution)
		btScalar _friction;			// ������ (Friction)
		btScalar _linearDamping;	// ���׷� (Damping)
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

	// inertia = ����
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
	
	// ������, ź����� (Restitution)
	void SetRestitution( btScalar value )
	{
		_property._restitution = value;
	}

	// ������ (Friction)
	void SetFriction( btScalar value )
	{
		_property._friction = value;
	}

	// ���׷� (Damping)
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

