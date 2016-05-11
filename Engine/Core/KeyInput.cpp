#include "CorePCH.h"
#include "KeyInput.h"


KeyInput::KeyInput()
{

}

KeyInput::~KeyInput()
{

}


void KeyInput::Init()
{
	for (int i = 0; i < 256; i++)
	{
		_keys[i] = false;
	}
}

// mutex
void KeyInput::KeyDown(unsigned int key)
{
	_keys[key] = true;
}

void KeyInput::KeyUp(unsigned int key)
{
	_keys[key] = false;
}

bool KeyInput::IsKeyDown(unsigned int key)
{
	return _keys[key];
}