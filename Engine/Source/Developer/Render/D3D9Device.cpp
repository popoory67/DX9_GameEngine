#include "RenderPCH.h"
#include "D3D9Device.h"

D3D9Ptr D3D9::_instance = nullptr;

D3D9::D3D9() : 
_d3d( nullptr ), 
_d3dDevice( nullptr ),
_screenWidth(0),
_screenHeight(0)
{
	ZeroMemory( &_d3dPP, sizeof( _d3dPP ) );
}

D3D9::~D3D9()
{
	Release();
}


D3D9Ptr D3D9::Get()
{
	if (!_instance)
	{
		_instance.reset( new D3D9() );
	}

	return _instance;
}

LPDIRECT3DDEVICE9 D3D9::GetDevice()
{
	return _d3dDevice;
}

LPDIRECT3DSURFACE9 D3D9::UseBuildRenderView( bool isUsedRenderView )
{
	if (isUsedRenderView)
	{
		if (FAILED( _d3dDevice->CreateRenderTarget( _screenWidth, _screenHeight,
													D3DFMT_A8R8G8B8, D3DMULTISAMPLE_NONE, 0,
													true, // lockable
													&_d3dSurface, NULL ) ))
		{
			assert( Util::ErrorMessage( "Failed to create D3D render target" ) );
		}

		_d3dDevice->SetRenderTarget( 0, _d3dSurface );
	}

	return _d3dSurface;
}


void D3D9::Init( HWND hWnd, bool screenMode, float screenWidth, float screenHeight )
{
	if (NULL == (_d3d = Direct3DCreate9( D3D_SDK_VERSION )))
	{
		assert( Util::ErrorMessage( "Failed to create D3D" ) );
	}

	D3DPRESENT_PARAMETERS d3dpp;

	ZeroMemory( &d3dpp, sizeof( d3dpp ) );

	if (screenMode)
		d3dpp.Windowed = FALSE;
	else
		d3dpp.Windowed = TRUE;

	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.EnableAutoDepthStencil = TRUE;
	d3dpp.AutoDepthStencilFormat = D3DFMT_D24S8;
	d3dpp.hDeviceWindow = hWnd;
	d3dpp.Flags = 0;
	d3dpp.MultiSampleType = D3DMULTISAMPLE_NONE;
	d3dpp.MultiSampleQuality = 0;
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;

	if (d3dpp.Windowed)
	{
		d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;
		//d3dpp.BackBufferWidth = D3DFMT_UNKNOWN;
		//d3dpp.BackBufferHeight = D3DFMT_UNKNOWN;
		d3dpp.BackBufferWidth = screenWidth;
		d3dpp.BackBufferHeight = screenHeight;
	}
	else
	{
		d3dpp.BackBufferFormat = D3DFMT_X8R8G8B8;
		d3dpp.BackBufferWidth = screenWidth;
		d3dpp.BackBufferHeight = screenHeight;
	}

	if (FAILED( _d3d->CreateDevice( D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL,
		hWnd, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp, &_d3dDevice ) ))
	{
		assert( Util::ErrorMessage( "Failed to create D3D device" ) );
	}

	_d3dPP = d3dpp;

	_screenWidth = screenWidth;
	_screenHeight = screenHeight;
}


void D3D9::Release()
{
	SAFE_RELEASE( _d3dDevice );
	SAFE_RELEASE( _d3d );
}

