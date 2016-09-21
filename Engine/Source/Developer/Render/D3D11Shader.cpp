#include "RenderPCH.h"
#include "D3D11Shader.h"
#include "Util.h"
#include "CreateD3D11.h"

D3D11Shader::D3D11Shader() : _vsBlob( nullptr ), _psBlob( nullptr ), _vsShader( nullptr ), _psShader( nullptr )
{
}


D3D11Shader::~D3D11Shader()
{
	SAFE_RELEASE( _vsBlob );
	SAFE_RELEASE( _psBlob );
	SAFE_RELEASE( _vsShader );
	SAFE_RELEASE( _psShader );
}


ShaderPtr D3D11Shader::Create()
{
	ShaderPtr shader( new D3D11Shader() );

	//shader->LoadShader( "" );

	return shader;
}

void D3D11Shader::LoadShader( const string& fileName )
{

}

HRESULT D3D11Shader::CreateVertexShader( const WCHAR* fileName, const LPCSTR entryPoint, const LPCSTR shaderModel )
{
	HRESULT hr = CompileShaderFromFile( fileName, entryPoint, shaderModel, &_vsBlob );

	if (FAILED( hr ))
	{
		assert( Util::ErrorMessage( "The FX file cannot be compiled." ) );
		return hr;
	}

	// Create the vertex shader
	hr = D3D11_DEVICE->CreateVertexShader( _vsBlob->GetBufferPointer(), _vsBlob->GetBufferSize(), NULL, &_vsShader );

	if (FAILED( hr ))
	{
		SAFE_RELEASE( _vsShader );
		SAFE_RELEASE( _vsBlob );

		return hr;
	}
}

HRESULT D3D11Shader::CreatePixelShader( const WCHAR* fileName, const LPCSTR entryPoint, const LPCSTR shaderModel )
{
	HRESULT hr = CompileShaderFromFile( fileName, entryPoint, shaderModel, &_psBlob );

	if (FAILED( hr ))
	{
		assert( Util::ErrorMessage( "The FX file cannot be compiled." ) );
		return hr;
	}

	// Create the pixel shader
	hr = D3D11_DEVICE->CreatePixelShader( _psBlob->GetBufferPointer(), _psBlob->GetBufferSize(), NULL, &_psShader );

	if (FAILED( hr ))
	{
		SAFE_RELEASE( _psShader );
		SAFE_RELEASE( _psBlob );

		return hr;
	}
}

HRESULT D3D11Shader::CompileShaderFromFile( const WCHAR* fileName, const LPCSTR entryPoint, const LPCSTR shaderModel, ID3DBlob** blobOut )
{
	DWORD shaderFlags = D3DCOMPILE_ENABLE_STRICTNESS;

#if defined( DEBUG ) || defined( _DEBUG )
	// Set the D3DCOMPILE_DEBUG flag to embed debug information in the shaders.
	shaderFlags |= D3DCOMPILE_DEBUG; 
#endif

	ID3DBlob* errorBlob = nullptr;

	HRESULT hr = D3DCompileFromFile( fileName, NULL, NULL, entryPoint, shaderModel,
									 shaderFlags, 0, blobOut, &errorBlob );

	if (FAILED( hr ))
	{
		if (errorBlob)
		{
			auto message = static_cast<char*>( errorBlob->GetBufferPointer() );
			OutputDebugStringA( message );
		}
	}

	if (errorBlob)
	{
		SAFE_RELEASE( errorBlob );
	}

	return hr;
}