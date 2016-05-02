#include "RenderPCH.h"
#include "Graphics.h"

#include "CreateDeviceD3DX.h"
//#include "CreateD3D11.h"
#include "Renderer.h"

//const bool FULL_SCREEN = false;
//const bool VSYNC_ENABLED = true;
//const float SCREEN_DEPTH = 1000.0f;
//const float SCREEN_NEAR = 0.1f;

Graphics::Graphics()
{

}


Graphics::~Graphics()
{

}

void Graphics::Init(HWND hWnd)
{
	// D3DX 초기화
	D3DX_INSTANCE.Init(hWnd);

	//bool result;
	//result = CreateD3D11::Get().Init(800, 600, VSYNC_ENABLED, hWnd, FULL_SCREEN, SCREEN_DEPTH, SCREEN_NEAR);

}

void Graphics::Release()
{
	Renderer::Get().Release();

}

void Graphics::RenderScene()
{
	if (!D3DX_DEVICE)
		return;

	D3DX_DEVICE->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0);

	if (D3DX_DEVICE->BeginScene())
	{
		// rendering option
		RenderState();

		// render mesh objects
		Renderer::Get().Render();

		D3DX_DEVICE->EndScene();
	}

	D3DX_DEVICE->Present(NULL, NULL, NULL, NULL);

	//CreateD3D11::Get().BeginScene(0.5f, 0.5f, 0.5f, 0.5f);

	//RenderState();
	//Renderer::Get().Render();

	//CreateD3D11::Get().EndScene();
}

void Graphics::RenderState()
{
	D3DX_DEVICE->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
	D3DX_DEVICE->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);

	D3DX_DEVICE->SetRenderState(D3DRS_ZENABLE, TRUE);		// Turn on the zbuffer
	D3DX_DEVICE->SetRenderState(D3DRS_AMBIENT, 0xffffffff);

	// alpha blend
	D3DX_DEVICE->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	D3DX_DEVICE->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	D3DX_DEVICE->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	// option : 기본컬링, CCW(반시계), CW(시계), NONE(컬링 안함)
	D3DX_DEVICE->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
}