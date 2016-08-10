#pragma once

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

