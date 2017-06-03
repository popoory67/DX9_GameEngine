#pragma once

#include "GameBehaviour.h"

class TestBehaviour : public GameBehaviour
{
public:
	TestBehaviour();
	~TestBehaviour();

	virtual void		Start() override;

	virtual void		Update() override;

	virtual void		Release() override;

};

