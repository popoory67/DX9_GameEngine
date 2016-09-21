#include "RenderPCH.h"
#include "D3D11Renderer.h"

#include "CreateD3D11.h"
#include "MeshManager.h"

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
	D3D11_INSTANCE->Init( 800, 600, VSYNC_ENABLED, hWnd, SCREEN_MODE, SCREEN_DEPTH, SCREEN_NEAR );
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