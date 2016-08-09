#pragma once

//#include <dxgi.h>
//#include <d3dcommon.h>
//#include <d3d11.h>
//#include <d3dx10math.h>
//
//#pragma comment(lib, "dxgi.lib")
//#pragma comment(lib, "d3d11.lib")
//#pragma comment(lib, "d3dx11.lib")
//#pragma comment(lib, "d3dx10.lib")


#define	D3D11_INSTANCE	CreateD3D11::Get()
#define D3D11_DEVICE	CreateD3D11::Get()->GetDevice()

#define FULL_SCREEN				false
#define VSYNC_ENABLED			true
#define SCREEN_DEPTH			1000.0f
#define SCREEN_NEAR				0.1f

//const bool	FULL_SCREEN			= false;
//const bool	VSYNC_ENABLED		= true;
//const float SCREEN_DEPTH		= 1000.0f;
//const float SCREEN_NEAR			= 0.1f;

class CreateD3D11;

using D3D11Ptr = shared_ptr<CreateD3D11>;

class CreateD3D11
{
public:
	
	~CreateD3D11();

	static D3D11Ptr Get();

	bool Init(int, int, bool, HWND, bool, float, float);
	void Release();

	void BeginScene(float, float, float, float);
	void EndScene();

	ID3D11Device* GetDevice();
	ID3D11DeviceContext* GetDeviceContext();

	void GetProjectionMatrix(D3DXMATRIX&);
	void GetWorldMatrix(D3DXMATRIX&);
	void GetOrthoMatrix(D3DXMATRIX&);

	void GetVideoCardInfo(char*, int&);

private:

	CreateD3D11();

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

	D3DXMATRIX _projectionMatrix;
	D3DXMATRIX _worldMatrix;
	D3DXMATRIX _orthoMatrix;
};
