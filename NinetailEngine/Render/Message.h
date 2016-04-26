#pragma once

#include "RenderPCH.h"

using namespace std;

class Message
{
public:
	Message();
	~Message();	
	
	// factory pattern
	static Message* Create();

	void AddMessageWithKey(string key, int message);
	void AddMessageWithKey(string key, float message);
	void AddMessageWithKey(string key, void* message);

	void AddMessage(int message);
	void AddMessage(float message);
	void AddMessage(void* message);

	int GetMessageIntWithKey(string key, unsigned int count = 0);
	float GetMessageFloatWithKey(string key, unsigned int count = 0);
	void* GetMessagePointerWithKey(string key, unsigned int count = 0);

	int GetMessageInt(unsigned int count = 0);
	float GetMessageFloat(unsigned int count = 0);
	void* GetMessagePointer(unsigned int count = 0);

private:

	void Init();

private:

	map<string, vector<int>>	_mapDataInt;
	map<string, vector<float>>	_mapDataFloat;
	map<string, vector<void*>>	_mapDataPointer;
	
	vector<int>					_vecDataInt;
	vector<float>				_vecDataFloat;
	vector<void*>				_vecDataPointer;

};

