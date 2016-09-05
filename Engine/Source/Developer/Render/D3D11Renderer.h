#pragma once

#include "RenderPCH.h"


const bool	VSYNC_ENABLED			= true;
const float SCREEN_DEPTH			= 1000.0f;
const float SCREEN_NEAR				= 0.1f;


class D3D11Renderer;

using D3D11RendererPtr = shared_ptr<D3D11Renderer>;

class D3D11Renderer
{
public:

	~D3D11Renderer();

	static D3D11RendererPtr Get();

	void Init( HWND hWnd );

	void RenderScene();

	void RenderState();

private:

	D3D11Renderer();

	static D3D11RendererPtr _instance;
};

