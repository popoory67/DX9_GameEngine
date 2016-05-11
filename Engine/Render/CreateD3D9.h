#pragma once

#include "RenderPCH.h"

#define SCREEN_WIDTH		1280
#define SCREEN_HEIGHT		720

#define	D3D9_INSTANCE		CreateD3D9::Get()
#define D3D9_DEVICE			CreateD3D9::Get().GetDevice()


class CreateD3D9 //DLLEXPORT CreateDeviceD3DX
{
public:

	~CreateD3D9();

	/**
	 * Gets the singleton instance of the create device d3dx class.
	 * @return the create device d3dx instance.
	 */
	static CreateD3D9& Get();

	LPDIRECT3DDEVICE9 GetDevice();

	void Init(HWND hWnd);

	void Release();

private:

	// 외부에서 생성하는 것을 막기 위해 생성자는 private에 선언한다
	CreateD3D9();

	void Create(HWND hWnd);

private:

	static CreateD3D9*		_instance;

	LPDIRECT3D9						_d3d;				// the pointer to our Direct3D interface
	LPDIRECT3DDEVICE9				_d3dDevice;			// the pointer to the device class
	D3DPRESENT_PARAMETERS			_d3dPP;
};