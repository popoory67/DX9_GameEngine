#pragma once

// Window screen : false
// Full screen : true
#define SCREEN_MODE			false

#define SCREEN_WIDTH		1280
#define SCREEN_HEIGHT		720


class D3D9Renderer;

using D3D9RendererPtr = shared_ptr<D3D9Renderer>;

class D3D9Renderer
{
public:

	~D3D9Renderer();

	static D3D9RendererPtr Get();

	void Init( HWND hWnd );

	void RenderScene();

	void RenderState();

private:

	D3D9Renderer();

private:

	static D3D9RendererPtr _instance;
};

