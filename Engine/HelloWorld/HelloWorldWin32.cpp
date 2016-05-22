#include "System.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	if (System::Get().Init())
	{
		System::Get().Run();
	}

	System::Get().Clear();
}

