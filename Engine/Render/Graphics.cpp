#include "RenderPCH.h"
#include "CreateDeviceD3DX.h"
#include "Graphics.h"



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