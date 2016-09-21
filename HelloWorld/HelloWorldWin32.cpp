#include "WindowSystem.h"
#include "Application.h"


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	if (WindowSystem::Get().Init())
	{
		// test
		GameObjectPtr game(new GameManager());
		GameObjectManager::Get().AddGame(game);

		WindowSystem::Get().Run();
	}

	WindowSystem::Get().Clear();
}