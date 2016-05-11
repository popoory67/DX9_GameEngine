#pragma once

#include "ModelParser.h"

class D3D11Renderer
{
public:

	D3D11Renderer();
	~D3D11Renderer();

	void Init(HWND hWnd);

	void Release();

	void RenderScene();

	void RenderState();

private:

	ModelParser*			_model;
};

