#include "CorePCH.h"
#include "Thread.h"
#include "ThreadManager.h"


Thread::Thread()
{

}

Thread::~Thread()
{

}

Thread* Thread::Create( function<void()> func )
{
	Thread* object = new Thread();

	object->Init( func );

	return object;
}

void Thread::Init( function<void()> func )
{
	auto threadfunc = bind( &Thread::Run, this, func );

	_thread = thread(threadfunc);
}

void Thread::Detach()
{
	_thread.detach();
}

void Thread::SetCallback( function<void( int )> func )
{
	_callback = func;
}


void Thread::Run( function<void()> func )
{
	func();

	// callback
	if (_callback)
	{
		_callback( _id );
	}

	// delete
	ThreadManager::Get().RemoveThread( _id );
}
