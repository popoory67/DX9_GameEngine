
#include "CreateWindowGL.h"


int main()
{
	CreateWindowGL*			window = new CreateWindowGL(true);

	window->Start();

	// �� ������ ����. �����찡 ����Ǳ� ������ �ݺ��Ѵ�.
	//while (window->GetRunning())
	while (!glfwWindowShouldClose(window->GetHWnd()))
	{
		window->Render();
		window->Update();
	}

	delete(window);	// define �ؾ���

	return 0;
}