#pragma once

class GameObject
{
public:
	GameObject();
	~GameObject();

	virtual void Start();

	virtual void Update();

	virtual void Release();
};

