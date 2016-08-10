#pragma once

#include "RenderPCH.h"

#define	SQUARE_SIZE			100

typedef struct _vertexData
{
	GLfloat			_posCoordinates[3];
	GLfloat			_texCoordinates[3];

} VertexData;


class CreateWindowGL
{
private:

	bool				_running;

	const char*			_title		= "test";
	GLfloat				_height;
	GLfloat				_width;

	GLFWwindow*			_hWnd;		// GLFW 윈도우 핸들러

private:

	GLuint				_vertexBufID;

public:

	CreateWindowGL(bool running);
	~CreateWindowGL();

	void				Init();

	void				Start();

	void				Render();

	void				Update();

	void				Clear();

public:

	bool				GetRunning();
	void				SetRunning(bool newRunning);

	GLFWwindow*			GetHWnd();

};

