#include "RenderPCH.h"
#include "Graphics.h"

#include "CreateD3D9.h"
#include "Renderer.h"


Graphics::Graphics()
{

}


Graphics::~Graphics()
{

}

void Graphics::Init(HWND hWnd)
{
	// D3D9 초기화
	D3D9_INSTANCE.Init(hWnd);
}

void Graphics::Release()
{
	Renderer::Get().Release();

	D3D9_INSTANCE.Release();
}

void Graphics::RenderScene()
{
	if (!D3D9_DEVICE)
		return;

	D3D9_DEVICE->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0);

	if (D3D9_DEVICE->BeginScene())
	{
		// rendering option
		RenderState();

		// render mesh objects
		Renderer::Get().Render();

		D3D9_DEVICE->EndScene();
	}

	D3D9_DEVICE->Present(NULL, NULL, NULL, NULL);

}

void Graphics::RenderState()
{
	D3D9_DEVICE->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
	D3D9_DEVICE->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);

	D3D9_DEVICE->SetRenderState(D3DRS_ZENABLE, TRUE);		// Turn on the zbuffer
	D3D9_DEVICE->SetRenderState(D3DRS_AMBIENT, 0xffffffff);

	// alpha blend
	D3D9_DEVICE->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	D3D9_DEVICE->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	D3D9_DEVICE->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	// option : 기본컬링, CCW(반시계), CW(시계), NONE(컬링 안함)
	D3D9_DEVICE->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
}