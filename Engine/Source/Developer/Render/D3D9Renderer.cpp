#include "RenderPCH.h"
#include "D3D9Renderer.h"

#include "CreateD3D9.h"
#include "MeshManager.h"


D3D9RendererPtr D3D9Renderer::_instance = nullptr;

D3D9Renderer::D3D9Renderer()
{

}

D3D9Renderer::~D3D9Renderer()
{

}

D3D9RendererPtr D3D9Renderer::Get()
{
	if (!_instance)
	{
		_instance.reset( new D3D9Renderer() );
	}

	return _instance;
}

void D3D9Renderer::Init( HWND hWnd )
{
	// D3D9 초기화
	D3D9_INSTANCE->Init( hWnd );
}


void D3D9Renderer::RenderScene()
{
	if (!D3D9_DEVICE)
	{
		assert( Util::ErrorMessage( "D3D device is null" ) );
	}

	D3D9_DEVICE->Clear( 0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB( 50, 50, 50 ), 1.0f, 0 );

	if (D3D9_DEVICE->BeginScene())
	{
		// rendering option
		RenderState();

		// render mesh objects
		MeshManager::Get()->Render();

		D3D9_DEVICE->EndScene();
	}

	D3D9_DEVICE->Present( NULL, NULL, NULL, NULL );

	D3D9_DEVICE->SetRenderState( D3DRS_FILLMODE, D3DFILL_SOLID );

}

void D3D9Renderer::RenderState()
{
	// original state
	D3D9_DEVICE->SetSamplerState( 0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR );
	D3D9_DEVICE->SetSamplerState( 0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR );

	D3D9_DEVICE->SetRenderState( D3DRS_ZENABLE, TRUE );		// Turn on the zbuffer
	D3D9_DEVICE->SetRenderState( D3DRS_AMBIENT, 0xffffffff );

	// alpha blend
	D3D9_DEVICE->SetRenderState( D3DRS_ALPHABLENDENABLE, TRUE );
	D3D9_DEVICE->SetRenderState( D3DRS_SRCBLEND, D3DBLEND_SRCALPHA );
	D3D9_DEVICE->SetRenderState( D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA );

	// option : 기본컬링, CCW(반시계), CW(시계), NONE(컬링 안함)
	D3D9_DEVICE->SetRenderState( D3DRS_CULLMODE, D3DCULL_CCW );

	// for sphere render
	D3D9_DEVICE->SetRenderState( D3DRS_LIGHTING, FALSE );
}