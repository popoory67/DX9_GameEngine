#include "RenderPCH.h"
#include "D3D9Shader.h"

#include "CreateD3D9.h"


D3D9Shader::D3D9Shader()
{

}

D3D9Shader::~D3D9Shader()
{
	SAFE_RELEASE( _d3dEffect );
}


ShaderPtr D3D9Shader::Create()
{
	ShaderPtr shader( new D3D9Shader() );

	shader->LoadShader( DEFAULT_SHADER );

	return shader;
}

void D3D9Shader::LoadShader( const string& fileName )
{
	LPD3DXBUFFER			error = NULL;
	DWORD					shaderFlags = 0;

	shaderFlags |= D3DXSHADER_DEBUG; // 컴파일러가 디버그 정보를 생성하도록 함

	auto openEffectFile = D3DXCreateEffectFromFile( D3D9_DEVICE, fileName.c_str(), NULL, NULL, shaderFlags, NULL, &_d3dEffect, &error );

	assert( !FAILED( openEffectFile ) );

	if (error)
	{
		SAFE_RELEASE( error );
	}
}