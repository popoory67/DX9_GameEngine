#include "DynamicWorld.h"


DynamicWorld* DynamicWorld::_instance = nullptr;

DynamicWorld::DynamicWorld()
{
}


DynamicWorld::~DynamicWorld()
{
	SAFE_DELETE( _dynamicsWorld );
	SAFE_DELETE( _solver );
	SAFE_DELETE( _dispatcher );
	SAFE_DELETE( _collisionConfiguration );
	SAFE_DELETE( _broadphase );
}

DynamicWorld* DynamicWorld::Get()
{
	if (!_instance)
	{
		_instance = DynamicWorld::Create();
	}

	return _instance;
}

DynamicWorld* DynamicWorld::Create()
{
	DynamicWorld* dynamicWorld( new DynamicWorld() );

	dynamicWorld->Init();

	return dynamicWorld;
}

void DynamicWorld::Init()
{
	// Build the broadphase      
	_broadphase = new btDbvtBroadphase();

	// Set up the collision configuration and dispatcher
	_collisionConfiguration = new btDefaultCollisionConfiguration();
	_dispatcher = new btCollisionDispatcher( _collisionConfiguration );

	// The actual physics solver
	_solver = new btSequentialImpulseConstraintSolver();

	// The world.
	_dynamicsWorld = new btDiscreteDynamicsWorld( _dispatcher, _broadphase, _solver, _collisionConfiguration );
	_dynamicsWorld->setGravity( btVector3( 0, -10, 0 ) );	// 중력의 방향과 크기
}