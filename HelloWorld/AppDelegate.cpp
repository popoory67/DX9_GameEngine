#include "AppDelegate.h"
#include "TestScene.h"

AppDelegate::AppDelegate()
{
}


AppDelegate::~AppDelegate()
{
}

void AppDelegate::Init()
{
	auto game = TestScene::Create();
}

void AppDelegate::Run()
{
	Init();

	Application::Run();
}