#pragma once

#include "RenderPCH.h"

// Window screen : false
// Full screen : true
#define SCREEN_MODE			false

#define SCREEN_WIDTH		1280
#define SCREEN_HEIGHT		720


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

