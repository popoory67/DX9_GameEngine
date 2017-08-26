#pragma once

#include "RenderPCH.h"
#include "D3DXRenderer.h"


class D3D11Renderer;

using D3D11RendererPtr = shared_ptr<D3D11Renderer>;

class D3D11Renderer : public D3DXRenderer
{
public:

	~D3D11Renderer();

	static D3D11RendererPtr Get();

	virtual void			Init(HWND hWnd);

	virtual void			RenderScene();

	virtual void			RenderState();

private:

	D3D11Renderer();

private:

	static D3D11RendererPtr _instance;
};

