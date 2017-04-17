#include "RenderPCH.h"
#include "Application.h"
#include "WindowSystem.h"


Application::Application()
{

}

Application::~Application()
{

}

void Application::Init()
{

}


void Application::Run()
{
	if (WindowSystem::Get().Init())
	{
		WindowSystem::Get().Run();
	}

	WindowSystem::Get().Clear();
}