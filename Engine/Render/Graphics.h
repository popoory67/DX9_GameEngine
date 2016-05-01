#pragma once

#include "Renderer.h"

class Graphics
{
public:

	Graphics();
	~Graphics();

	void Init(HWND hWnd);

	void Release();

	void RenderScene();

	void RenderState();

private:

};

