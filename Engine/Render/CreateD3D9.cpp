#include "RenderPCH.h"
#include "CreateD3D9.h"

CreateD3D9* CreateD3D9::_instance = NULL;

CreateD3D9::CreateD3D9() : _d3d(NULL), _d3dDevice(NULL)
{
	ZeroMemory(&_d3dPP, sizeof(_d3dPP));
}

CreateD3D9::~CreateD3D9()
{
	if (_instance)
	{
		SAFE_RELEASE(_instance);
	}
}


CreateD3D9& CreateD3D9::Get()
{
	if (!_instance)
	{
		_instance = new CreateD3D9();
	}

	return *_instance;
}

LPDIRECT3DDEVICE9 CreateD3D9::GetDevice()
{
	return _d3dDevice;
}

void CreateD3D9::Create(HWND hWnd)
{
	if (NULL == (_d3d = Direct3DCreate9(D3D_SDK_VERSION)))
		return;

	D3DPRESENT_PARAMETERS d3dpp;

	ZeroMemory(&d3dpp, sizeof(d3dpp));

	if (WINDOW_MODE)
		d3dpp.Windowed = TRUE;
	else
		d3dpp.Windowed = FALSE;

	d3dpp.SwapEffect				= D3DSWAPEFFECT_DISCARD;
	d3dpp.EnableAutoDepthStencil	= TRUE;
	d3dpp.AutoDepthStencilFormat	= D3DFMT_D24S8;
	d3dpp.hDeviceWindow				= hWnd;
	d3dpp.Flags						= 0;
	d3dpp.MultiSampleType			= D3DMULTISAMPLE_NONE;
	d3dpp.MultiSampleQuality		= 0;
	d3dpp.PresentationInterval		= D3DPRESENT_INTERVAL_IMMEDIATE;

	if (d3dpp.Windowed)
	{
		d3dpp.BackBufferFormat		= D3DFMT_UNKNOWN;
		d3dpp.BackBufferWidth		= D3DFMT_UNKNOWN;
		d3dpp.BackBufferHeight		= D3DFMT_UNKNOWN;
	}
	else
	{
		d3dpp.BackBufferFormat		= D3DFMT_X8R8G8B8;
		d3dpp.BackBufferWidth		= SCREEN_WIDTH;
		d3dpp.BackBufferHeight		= SCREEN_HEIGHT;
	}

	if (FAILED(_d3d->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp, &_d3dDevice)))
	{
		return;
	}

	_d3dPP = d3dpp;
}

void CreateD3D9::Init(HWND hWnd)
{
	Create(hWnd);

	if (_d3d)
	{
		if (_d3dDevice)
			_d3dDevice->Reset(&_d3dPP);
	}
}


void CreateD3D9::Release()
{
	SAFE_RELEASE(_d3dDevice);
	SAFE_RELEASE(_d3d);
}

