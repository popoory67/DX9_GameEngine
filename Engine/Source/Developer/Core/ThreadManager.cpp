#include "CorePCH.h"
#include "ThreadManager.h"

ThreadManager* ThreadManager::_instance = nullptr;

ThreadManager::ThreadManager() : _idCount( 0 )
{

}

ThreadManager::~ThreadManager()
{
	if (_instance)
	{
		delete _instance;
	}
}


ThreadManager& ThreadManager::Get()
{
	if (!_instance)
	{
		_instance = new ThreadManager();
	}

	return *_instance;
}

int ThreadManager::AddThread( function<void()> func )
{
	return AddThread( func, nullptr );
}

int ThreadManager::AddThread( function<void()> func, function<void( int )> callback )
{
	Thread* thread = Thread::Create( func );

	int id = _idCount;

	thread->SetID( id );
	thread->SetCallback( callback );

	_thread.push_back( thread );

	_idCount++;

	return _idCount;
}

void ThreadManager::Update()
{
	if (_removeThread.size() > 0)
	{
		for (int i = 0; i < _removeThread.size(); i++)
		{
			for (auto it = _thread.begin(); it != _thread.end();) //it++)
			{
				if ((*it)->GetID() == _removeThread[i])
				{
					(*it)->Detach();

					delete (*it);
					(*it) = nullptr;

					_thread.erase( it++ );

					break;
				}

				else
				{
					it++;
				}
			}
		}

		// 쓰레드를 삭제한 뒤 클리어하는 것으로 루프문 낭비를 최소화
		_removeThread.clear();
	}
}

void ThreadManager::RemoveThread( int id )
{
	_removeThread.push_back( id );
}

Thread* ThreadManager::GetThread( int id )
{
	// find thread
	for (auto it = _thread.begin(); it != _thread.end(); it++)
	{
		if ((*it)->GetID() == id)
		{
			return *it;
		}
	}

	// the thread dosen't exist
	return nullptr;
}
