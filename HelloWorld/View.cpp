#include "View.h"
#include <iostream>
#include <functional>
#include "MessageDispatcher.h"

View::View()
{
	test = new DynamicWorld();
}

View::~View()
{

}

View* View::Create()
{
	View* view( new View() );

	view->Init();

	return view;
}

void View::Init()
{
	FuncMessage func = std::bind( &View::Render, this, placeholders::_1 );

	MessageDispatcher::Get()->AddObserver( COLLISION_TEST, func );
}

// init
void View::Render( Message* msg )
{
	float* y = (float*)msg->GetMessagePointerWithKey( "y" );
}

// update
void View::CollisionTest()
{
	/*--- 땅 객체의 충돌체 ---*/
	// ground의 모양
	btCollisionShape* groundShape = new btStaticPlaneShape( btVector3( 0, 1, 0 ), 1 );

	// Set default ground state
	btDefaultMotionState* groundMotionState = new btDefaultMotionState( btTransform( btQuaternion( 0, 0, 0, 1 ), btVector3( 0, -1, 0 ) ) );
	btRigidBody::btRigidBodyConstructionInfo
		groundRigidBodyCI( 0, groundMotionState, groundShape, btVector3( 0, 0, 0 ) );
	btRigidBody* groundRigidBody = new btRigidBody( groundRigidBodyCI );
//	test->GetDynamicWorld().addRigidBody( groundRigidBody );

	/*--- 떨어지는 객체의 충돌체 ---*/
	// 떨어지는 객체의 충돌체 모양
	btCollisionShape* fallShape = new btSphereShape( 1 );

	// Set default fall state ( rotation, position )
	btDefaultMotionState* fallMotionState =
		new btDefaultMotionState( btTransform( btQuaternion( 0, 0, 0, 1 ), btVector3( 0, 50, 0 ) ) );
	btScalar mass = 1;	// 질량
	btVector3 fallInertia( 0, 0, 0 );
	fallShape->calculateLocalInertia( mass, fallInertia );
	btRigidBody::btRigidBodyConstructionInfo fallRigidBodyCI( mass, fallMotionState, fallShape, fallInertia );
	btRigidBody* fallRigidBody = new btRigidBody( fallRigidBodyCI );
//	test->GetDynamicWorld().addRigidBody( fallRigidBody );


	for (int i = 0; i < 300; i++)
	{
//		test->GetDynamicWorld().stepSimulation( 1 / 60.f, 10 );

		btTransform trans;
		fallRigidBody->getMotionState()->getWorldTransform( trans );

		Message* msg = Message::Create();

		float y = trans.getOrigin().getY();
		msg->AddMessageWithKey( "y", &y );
		MessageDispatcher::Get()->SendMessage( COLLISION_TEST, msg );
		//std::cout << "sphere height: " << trans.getOrigin().getY() << std::endl;
	}

	// Clean up behind ourselves like good little programmers
//	test->GetDynamicWorld().removeRigidBody( fallRigidBody );
	delete fallRigidBody->getMotionState();
	delete fallRigidBody;

//	test->GetDynamicWorld().removeRigidBody( groundRigidBody );
	delete groundRigidBody->getMotionState();
	delete groundRigidBody;


	delete fallShape;

	delete groundShape;
}