#pragma once

#include "RenderPCH.h"

#define SCREEN_WIDTH		1280
#define SCREEN_HEIGHT		720

#define	D3DX_INSTANCE	CreateDeviceD3DX::Get()
#define D3DX_DEVICE		CreateDeviceD3DX::Get().GetDevice()


class CreateDeviceD3DX //DLLEXPORT CreateDeviceD3DX
{
public:

	~CreateDeviceD3DX();

	/**
	 * Gets the singleton instance of the create device d3dx class.
	 * @return the create device d3dx instance.
	 */
	static CreateDeviceD3DX& Get();

	LPDIRECT3DDEVICE9 GetDevice();

	void Init(HWND hWnd);

	void Release();

private:

	// 외부에서 생성하는 것을 막기 위해 생성자는 private에 선언한다
	CreateDeviceD3DX();

	void Create(HWND hWnd);

private:

	static CreateDeviceD3DX*		_instance;

	LPDIRECT3D9						_d3d;				// the pointer to our Direct3D interface
	LPDIRECT3DDEVICE9				_d3dDevice;			// the pointer to the device class
	D3DPRESENT_PARAMETERS			_d3dPP;
};