#pragma once

#include <d3d11.h>
#include <DirectXMath.h>
#include "D3DXDevice.h"

using namespace std;
using namespace DirectX;	// included from windows 8.1

#define	D3D11_INSTANCE			D3D11::Get()
#define D3D11_DEVICE			D3D11::Get()->GetDevice()
#define D3D11_DEVICE_CONTEXT	D3D11::Get()->GetDeviceContext()


class D3D11;

using D3D11Ptr = shared_ptr<D3D11>;

class D3D11 : public D3DXDevice
{
public:

	virtual ~D3D11();

	static D3D11Ptr Get();

	ID3D11Device* GetDevice();
	ID3D11DeviceContext* GetDeviceContext();

	void GetProjectionMatrix( XMMATRIX& projectionMatrix );
	void GetWorldMatrix( XMMATRIX& worldMatrix );
	void GetOrthoMatrix( XMMATRIX& orthoMatrix );

	void GetVideoCardInfo( char* cardName, int& memory );

	virtual void Init( HWND hWnd, bool screenMode, float screenWidth, float screenHeight );
	virtual void Release();

	void BeginScene( float red, float green, float blue, float alpha );
	void EndScene();

private:

	D3D11();

private:

	static D3D11Ptr _instance;

	bool _vsyncEnabled;
	int _videoCardMemory;
	char _videoCardDescription[128];

	IDXGISwapChain* _swapChain;
	ID3D11Device* _device;
	ID3D11DeviceContext* _deviceContext;
	ID3D11RenderTargetView* _renderTargetView;
	ID3D11Texture2D* _depthStencilBuffer;
	ID3D11DepthStencilState* _depthStencilState;
	ID3D11DepthStencilView* _depthStencilView;
	ID3D11RasterizerState* _rasterState;

	//ID3D11BlendState*				g_pBlendState = nullptr;
	//ID3D11Buffer*					g_pcBuffer = nullptr;
	//ID3D11VertexShader*                 g_pvsFBX = nullptr;
	//ID3D11PixelShader*                  g_ppsFBX = nullptr;

	XMMATRIX _projectionMatrix;
	XMMATRIX _worldMatrix;
	XMMATRIX _orthoMatrix;
};
