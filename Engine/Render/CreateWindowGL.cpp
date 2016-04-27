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
	// ���� ���ؽ�Ʈ ����(������)�� ��ȯ
	glfwMakeContextCurrent(_hWnd);

	// swap ���� ����
	glfwSwapInterval(1);

	// Ű �ڵ鷯 ���
	//glfwSetKeyCallback(window, KeyCallback);

	// ������ ������ ���� �ڵ鷯 ���
	//glfwSetWindowSizeCallback(window, WindowSizeChangeCallback);

	// GLEW �ʱ�ȭ
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
	// ���� �����
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glColor3f(1.0f, .0f, .0f);

	glDrawArrays(GL_QUADS, 0, 4);

	// ���� ���� ��ü. (�׸� ����� ���÷����ϴ� ���)
	glfwSwapBuffers(_hWnd);

	// ������ �̺�Ʈ (Ű ��Ʈ��ũ ��) ����.
	glfwPollEvents();

}

void CreateWindowGL::Update()
{

}

void CreateWindowGL::Clear()
{
	// ������ ����
	glfwDestroyWindow(_hWnd);

	// GLFW ����
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