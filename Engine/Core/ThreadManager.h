#pragma once

#include "Thread.h"

class ThreadManager
{
public:
	
	~ThreadManager();

	static ThreadManager& Get();

	int AddThread(Thread* thread);

	int AddThread(Thread* thread, function<void(int)> callback);

	int AddThread(function<void()> func);

	int AddThread(function<void()> func, function<void(int)> callback);

	void Update();

	void RemoveThread(int id);

	Thread* GetThread(int id);

private:

	ThreadManager();

private:

	static ThreadManager* _instance;

	int _idCount;

	vector<Thread*> _thread;

	vector<int> _removeThread;
};

