#include "RenderPCH.h"
#include "D3D11Renderer.h"

#include "CreateD3D11.h"

#define DRAGON		"C:/Users/boseul/Documents/GitHub/NinetailEngine/Engine/Resource/cube.txt"
#define DRAGON_TEX	L"C:/Users/boseul/Documents/GitHub/NinetailEngine/Engine/Resource/seafloor.dds"

D3D11Renderer::D3D11Renderer()
{
	_model = new ModelParser();
}


D3D11Renderer::~D3D11Renderer()
{
}


void D3D11Renderer::Init(HWND hWnd)
{
	// D3D11 ÃÊ±âÈ­
	D3D11_INSTANCE.Init(800, 600, VSYNC_ENABLED, hWnd, FULL_SCREEN, SCREEN_DEPTH, SCREEN_NEAR);

	//_model->Initialize(D3D11_DEVICE, DRAGON, DRAGON_TEX);
}

void D3D11Renderer::Release()
{
	D3D11_INSTANCE.Release();
}

void D3D11Renderer::RenderScene()
{
	// d3d11
	D3D11_INSTANCE.BeginScene(0.f, 0.f, 0.f, 0.f);

	RenderState();
	_model->Render(D3D11_INSTANCE.GetDeviceContext());
	//Renderer::Get().Render();
	 
	D3D11_INSTANCE.EndScene();
}

void D3D11Renderer::RenderState()
{

}