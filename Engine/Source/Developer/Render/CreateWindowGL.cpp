#pragma once

#include "RenderPCH.h"

#include "CreateWindowGL.h"

VertexData _vertices[] =
{
	{ { 0, 0, 0 }, {0, 0} },
	{ { SQUARE_SIZE, 0, 0 }, {1, 0} },
	{ { SQUARE_SIZE, SQUARE_SIZE, 0 }, {1, 1} },
	{ { 0, SQUARE_SIZE, 0 }, {0, 1} }
};


CreateWindowGL::CreateWindowGL(bool running) : 
_running(false), _hWnd(NULL), _height(500), _width(_height / 9 * 16),
_vertexBufID(0)
{
	_running = running;

	Init();
}

CreateWindowGL::~CreateWindowGL()
{
	Clear();
}

void CreateWindowGL::Init()
{
	if (!glfwInit())
	{
		exit(EXIT_FAILURE);
	}

	_hWnd = glfwCreateWindow(_width, _height, _title, NULL, NULL);

	if (!_hWnd)
	{
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	glMatrixMode(GL_PROJECTION);
	glMatrixMode(GL_MODELVIEW);
}

void CreateWindowGL::Start()
{
	// 현재 컨텍스트 상태(쓰레드)를 반환
	glfwMakeContextCurrent(_hWnd);

	// swap 간격 조정
	glfwSwapInterval(1);

	// 키 핸들러 등록
	//glfwSetKeyCallback(window, KeyCallback);

	// 윈도우 사이즈 변경 핸들러 등록
	//glfwSetWindowSizeCallback(window, WindowSizeChangeCallback);

	// GLEW 초기화
	glewInit();

	glViewport(0, 0, _width, _height);
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

	glGenBuffers(1, &_vertexBufID);
	glBindBuffer(GL_ARRAY_BUFFER, _vertexBufID);
	glBufferData(GL_ARRAY_BUFFER, sizeof(_vertices), _vertices, GL_STATIC_DRAW);

	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3, GL_FLOAT, sizeof(VertexData), (GLvoid*)
		offsetof(VertexData, _posCoordinates));

	//glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	//glTexCoordPointer(2, GL_FLOAT, sizeof(VertexData), (GLvoid*)
	//	offsetof(VertexData, _texCoordinates));
}

void CreateWindowGL::Render()
{
	// 버퍼 지우기
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glColor3f(1.0f, .0f, .0f);

	glDrawArrays(GL_QUADS, 0, 4);

	// 렌더 버퍼 교체. (그린 결과를 디스플레이하는 명령)
	glfwSwapBuffers(_hWnd);

	// 윈도우 이벤트 (키 스트로크 등) 폴링.
	glfwPollEvents();

}

void CreateWindowGL::Update()
{

}

void CreateWindowGL::Clear()
{
	// 윈도우 제거
	glfwDestroyWindow(_hWnd);

	// GLFW 종료
	glfwTerminate();
}



bool CreateWindowGL::GetRunning()
{
	return _running;
}

void CreateWindowGL::SetRunning(bool newRunning)
{
	_running = newRunning;
}

GLFWwindow* CreateWindowGL::GetHWnd()
{
	return _hWnd;
}