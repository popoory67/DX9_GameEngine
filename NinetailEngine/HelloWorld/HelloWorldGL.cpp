
#include "CreateWindowGL.h"


int main()
{
	CreateWindowGL*			window = new CreateWindowGL(true);

	window->Start();

	// 주 렌더링 루프. 윈도우가 종료되기 전까지 반복한다.
	//while (window->GetRunning())
	while (!glfwWindowShouldClose(window->GetHWnd()))
	{
		window->Render();
		window->Update();
	}

	delete(window);	// define 해야함

	return 0;
}