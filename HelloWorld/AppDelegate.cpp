#include "AppDelegate.h"
#include "TestScene.h"

AppDelegate::AppDelegate()
{
}


AppDelegate::~AppDelegate()
{
}

void AppDelegate::Run()
{
	Application::Run();	
	
	TestScene::Create();
}