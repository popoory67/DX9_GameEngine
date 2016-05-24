#pragma once


class KeyInput
{
public:
	KeyInput();
	~KeyInput();

	static KeyInput* Create();

	void Init();

	void KeyDown(unsigned int);

	void KeyUp(unsigned int);

	bool IsKeyDown(unsigned int);

private:

	bool _keys[256];
};

