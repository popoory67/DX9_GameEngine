#include "WindowSystem.h"
#include "Application.h"


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	if (WindowSystem::Get().Init())
	{
		// test
		GameBehaviourPtr game( new MyGameManager() );
		BehaviourManager::Get().AddGame( game );

		WindowSystem::Get().Run();
	}

	WindowSystem::Get().Clear();
}