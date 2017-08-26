#include "CorePCH.h"
#include "Component.h"
#include "Thread.h"


Component::Component()
{
	_voidObservers	= new VObservers();
	_msgObservers	= new MObservers();
}

Component::~Component()
{
	SAFE_DELETE(_voidObservers);
	SAFE_DELETE(_msgObservers);

	SAFE_DELETE(_gameObject);
}

void Component::AddObserver(string key, FuncVoid func)
{
	auto iter = _voidObservers->lower_bound(key);

	// If you don't have the key
	if (iter == end(*_voidObservers) || _voidObservers->key_comp()(key, iter->first))
	{
		vector< FuncVoid > vec;
		vec.push_back(func);

		iter = _voidObservers->insert(iter, make_pair(key, vec));
	}

	else
	{
		(*_voidObservers)[key].push_back(func);
	}
}


void Component::AddObserver(string key, FuncMessage func)
{
	auto iter = _msgObservers->lower_bound(key);

	// If you don't have the key
	if (iter == end(*_msgObservers) || _msgObservers->key_comp()(key, iter->first))
	{
		vector< FuncMessage > vec;
		vec.push_back(func);

		iter = _msgObservers->insert(iter, make_pair(key, vec));
	}

	else
	{
		(*_msgObservers)[key].push_back(func);
	}
}


void Component::SendMessageToObservers(string key)
{
	SendMessageToObservers(key, NULL);
}


void Component::SendMessageToObservers(string key, Message* message)
{
	Thread* vThread = nullptr;
	Thread* mThread = nullptr;

	if (_voidObservers->find(key) != _voidObservers->end())
	{
		vThread = Thread::Create([&]()
		{
			auto vObservers = (*_voidObservers)[key];

			for (auto i = 0; i < vObservers.size(); i++)
			{
				vObservers[i]();
			}
		});
	}

	if (_msgObservers->find(key) != _msgObservers->end())
	{
		mThread = Thread::Create([&]()
		{
			auto mObservers = (*_msgObservers)[key];

			for (auto i = 0; i < mObservers.size(); i++)
			{
				mObservers[i](message);
			}
		});
	}

	if (vThread)
		vThread->Update();

	if (mThread)
		mThread->Update();

	SAFE_DELETE(vThread);
	SAFE_DELETE(mThread);

	if (message)
	{
		SAFE_DELETE(message);
	}
}