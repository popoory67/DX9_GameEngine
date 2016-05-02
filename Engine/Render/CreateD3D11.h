#pragma once


class CreateD3D11
{
public:
	
	~CreateD3D11();

	static CreateD3D11&		Get();

	bool					Init(int, int, bool, HWND, bool, float, float);
	void					Release();

	void					BeginScene(float, float, float, float);
	void					EndScene();

	ID3D11Device*			GetDevice();
	ID3D11DeviceContext*	GetDeviceContext();

	void					GetProjectionMatrix(D3DXMATRIX&);
	void					GetWorldMatrix(D3DXMATRIX&);
	void					GetOrthoMatrix(D3DXMATRIX&);

	void					GetVideoCardInfo(char*, int&);

private:

	CreateD3D11();

private:

	static CreateD3D11*				_instance;

	bool							_vsyncEnabled;
	int								_videoCardMemory;
	char							_videoCardDescription[128];

	IDXGISwapChain*					_swapChain;
	ID3D11Device*					_device;
	ID3D11DeviceContext*			_deviceContext;
	ID3D11RenderTargetView*			_renderTargetView;
	ID3D11Texture2D*				_depthStencilBuffer;
	ID3D11DepthStencilState*		_depthStencilState;
	ID3D11DepthStencilView*			_depthStencilView;
	ID3D11RasterizerState*			_rasterState;

	D3DXMATRIX						_projectionMatrix;
	D3DXMATRIX						_worldMatrix;
	D3DXMATRIX						_orthoMatrix;
};

#define	D3D11_INSTANCE		CreateD3D11::Get()
#define D3D11_DEVICE		CreateD3D11::Get().GetDevice()