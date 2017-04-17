#pragma once

#define KEY_INPUT		KeyInput::Get()

class KeyInput
{
public:

	~KeyInput();

	static KeyInput& Get();

	static KeyInput* Create();

	void Init();

	void KeyDown( unsigned int key );

	void KeyUp( unsigned int key );

	bool IsKeyDown( unsigned int key );

	void Clear();
	
private:

	KeyInput();

private:

	static KeyInput* _instance;

	bool _keys[256];
};

