#pragma once

#include "CreateDeviceD3DX.h"

class View
{
public:

	View()
	{

	}
	~View()
	{

	}

	void Init()
	{
		D3DXMATRIXA16 matWorld;
		D3DXMatrixRotationY(&matWorld, timeGetTime() / 1000.0f);
		D3DX_DEVICE->SetTransform(D3DTS_WORLD, &matWorld);

		D3DXVECTOR3 vEyePt(0.0f, 3.0f, -70.0f);
		D3DXVECTOR3 vLookatPt(0.0f, 0.0f, 0.0f);
		D3DXVECTOR3 vUpVec(0.0f, 1.0f, 0.0f);
		D3DXMATRIXA16 matView;
		D3DXMatrixLookAtLH(&matView, &vEyePt, &vLookatPt, &vUpVec);
		D3DX_DEVICE->SetTransform(D3DTS_VIEW, &matView);

		D3DXMATRIXA16 matProj;
		D3DXMatrixPerspectiveFovLH(&matProj, D3DX_PI / 4, 1.0f, 1.0f, 100.0f);
		D3DX_DEVICE->SetTransform(D3DTS_PROJECTION, &matProj);
	}

private:

};
