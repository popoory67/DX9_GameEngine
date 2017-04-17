#pragma once

#include "Application.h"

class AppDelegate : public Application
{
public:
	AppDelegate();
	virtual ~AppDelegate();

	virtual void Init();
	virtual void Run();
};

