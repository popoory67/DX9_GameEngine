
/*
 * We except D3Dcommon.h, D3Dcompiler.h in DirectX SDK for using d3dcompiler.h including windows 8.1.
 */

#pragma once

#include <d3d11.h>
#include <d3dcompiler.h>
#include "D3DXShader.h"

class D3D11Shader;

using ShaderPtr = shared_ptr<D3D11Shader>;

class D3D11Shader : public D3DXShader
{
public:
	D3D11Shader();
	virtual ~D3D11Shader();

	static ShaderPtr	Create();

	virtual void		LoadShader( const string& fileName );

	HRESULT				CreateVertexShader( const WCHAR* fileName, const LPCSTR entryPoint, const LPCSTR shaderModel );
	HRESULT				CreatePixelShader( const WCHAR* fileName, const LPCSTR entryPoint, const LPCSTR shaderModel );

private:

	HRESULT				CompileShaderFromFile( const WCHAR* fileName, const LPCSTR entryPoint, const LPCSTR shaderModel, ID3DBlob** blobOut );

private:

	// ID3DBlob is used to return data of arbitrary length.
	ID3DBlob*			_vsBlob		= nullptr;
	ID3DBlob*			_psBlob		= nullptr;

	ID3D11VertexShader* _vsShader	= nullptr;	// vertex shader
	ID3D11PixelShader*	_psShader	= nullptr;	// pixel shader
};

