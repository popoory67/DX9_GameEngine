#include "RenderPCH.h"
#include "D3D11Renderer.h"

#include "D3D11Device.h"
#include "MeshManager.h"

// Window screen : false
// Full screen : true
#define SCREEN_MODE			false

#define SCREEN_WIDTH		1280
#define SCREEN_HEIGHT		720


D3D11RendererPtr D3D11Renderer::_instance = nullptr;

D3D11Renderer::D3D11Renderer()
{

}

D3D11Renderer::~D3D11Renderer()
{

}

D3D11RendererPtr D3D11Renderer::Get()
{
	if (!_instance)
	{
		_instance.reset( new D3D11Renderer() );
	}

	return _instance;
}


void D3D11Renderer::Init( HWND hWnd )
{
	if (!D3D11_INSTANCE)
	{
		assert( Util::ErrorMessage( "D3D device is null" ) );
	}

	// D3D11 ÃÊ±âÈ­
	D3D11_INSTANCE->Init( hWnd, SCREEN_MODE, SCREEN_WIDTH, SCREEN_HEIGHT );
}


void D3D11Renderer::RenderScene()
{
	// d3d11
	D3D11_INSTANCE->BeginScene( 0.f, 0.f, 0.f, 0.f );

	RenderState();

	MeshManager::Get()->Render();

	D3D11_INSTANCE->EndScene();
}

void D3D11Renderer::RenderState()
{

}