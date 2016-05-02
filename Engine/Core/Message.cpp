#include "CorePCH.h"
#include "Message.h"


Message::Message()
{
}


Message::~Message()
{
}


Message* Message::Create()
{
	Message* object = new Message();

	object->Init();

	return object;
}

void Message::AddMessageWithKey(string key, int message)
{
	_mapDataInt[key].push_back(message);
}

void Message::AddMessageWithKey(string key, float message)
{
	_mapDataFloat[key].push_back(message);
}

void Message::AddMessageWithKey(string key, void* message)
{
	_mapDataPointer[key].push_back(message);
}

void Message::AddMessage(int message)
{
	_vecDataInt.push_back(message);
}

void Message::AddMessage(float message)
{
	_vecDataFloat.push_back(message);
}

void Message::AddMessage(void* message)
{
	_vecDataPointer.push_back(message);
}

int Message::GetMessageIntWithKey(string key, unsigned int count/* = 0*/)
{
	if (_mapDataInt.find(key) != _mapDataInt.end())
	{
		if (_mapDataInt[key].size() > count)
		{
			return _mapDataInt[key][count];
		}
	}

	// Assert //

	return 0;
}

float Message::GetMessageFloatWithKey(string key, unsigned int count/* = 0*/)
{
	if (_mapDataFloat.find(key) != _mapDataFloat.end())
	{
		if (_mapDataFloat[key].size() > count)
		{
			return _mapDataFloat[key][count];
		}
	}

	// Assert //

	return 0;
}

void* Message::GetMessagePointerWithKey(string key, unsigned int count/* = 0*/)
{
	if (_mapDataPointer.find(key) != _mapDataPointer.end())
	{
		if (_mapDataPointer[key].size() > count)
		{
			return _mapDataPointer[key][count];
		}
	}

	// Assert //

	return NULL;
}

int Message::GetMessageInt(unsigned int count/* = 0*/)
{
	if (_vecDataInt.size() > count)
	{
		return _vecDataInt[count];
	}

	// Assert //

	return 0;
}

float Message::GetMessageFloat(unsigned int count/* = 0*/)
{
	if (_vecDataFloat.size() > count)
	{
		return _vecDataFloat[count];
	}

	// Assert //

	return 0;
}

void* Message::GetMessagePointer(unsigned int count/* = 0*/)
{
	if (_vecDataPointer.size() > count)
	{
		return _vecDataPointer[count];
	}

	// Assert //

	return NULL;
}


void Message::Init()
{
	_mapDataInt.clear();
	_mapDataFloat.clear();
	_mapDataPointer.clear();

	_vecDataInt.clear();
	_vecDataFloat.clear();
	_vecDataPointer.clear();
}