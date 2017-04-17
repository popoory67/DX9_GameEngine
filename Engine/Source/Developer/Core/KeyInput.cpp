#include "CorePCH.h"
#include "KeyInput.h"

KeyInput* KeyInput::_instance = nullptr;

KeyInput::KeyInput()
{

}

KeyInput::~KeyInput()
{

}

KeyInput& KeyInput::Get()
{
	if (!_instance)
	{
		_instance = KeyInput::Create();
	}

	return *_instance;
}


KeyInput* KeyInput::Create()
{
	KeyInput* key = new KeyInput();

	key->Init();

	return key;
}


void KeyInput::Init()
{
	for (int i = 0; i < 256; i++)
	{
		_keys[i] = false;
	}
}

// mutex
void KeyInput::KeyDown( unsigned int key )
{
	_keys[key] = true;
}

void KeyInput::KeyUp( unsigned int key )
{
	_keys[key] = false;
}

bool KeyInput::IsKeyDown( unsigned int key )
{
	return _keys[key];
}

void KeyInput::Clear()
{
	if (_keys)
	{
		delete[] _keys;
	}
}