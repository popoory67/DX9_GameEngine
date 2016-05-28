#pragma once

#define KEY_INPUT		KeyInput::Get()

class KeyInput
{
public:
	
	~KeyInput();

	static KeyInput& Get();

	static KeyInput* Create();

	void Init();

	void KeyDown(unsigned int);

	void KeyUp(unsigned int);

	bool IsKeyDown(unsigned int);

	void Clear();

private:

	KeyInput();

private:

	static KeyInput* _instance;

	bool _keys[256];
};

