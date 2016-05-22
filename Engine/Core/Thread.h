#pragma once

class Thread
{
public:
	
	Thread();
	~Thread();

	static Thread* Create(function<void()> func);

	void Init(function<void()> func);

	void Detach();

	void Destroy();

	void SetCallback(function<void(int)> func);

	int GetID();

	void SetID(int id);

private:

	void Run(function<void()> func);

private:

	thread _thread;

	int _id								= 0;

	function<void(int)> _callback		= nullptr;
};

