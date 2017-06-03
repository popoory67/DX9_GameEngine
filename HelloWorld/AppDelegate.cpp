#include "AppDelegate.h"
#include "TestScene.h"
#include "WindowSystem.h"

AppDelegate::AppDelegate()
{
}


AppDelegate::~AppDelegate()
{
}

void AppDelegate::Run()
{
	TestScene::Create();

	Application::Run();
}