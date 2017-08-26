#pragma once

#include "D3DXRenderer.h"


class D3D9Renderer;

using D3D9RendererPtr = shared_ptr<D3D9Renderer>;

class D3D9Renderer : public D3DXRenderer
{
public:

	~D3D9Renderer();

	static D3D9RendererPtr	Get();

	virtual void			Init(HWND hWnd);

	virtual void			RenderScene();

	virtual void			RenderState();

private:

	D3D9Renderer();

private:

	static D3D9RendererPtr		_instance;
};

