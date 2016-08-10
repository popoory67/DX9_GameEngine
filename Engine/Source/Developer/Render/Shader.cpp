#include "RenderPCH.h"
#include "Shader.h"

#include "CreateD3D9.h"


Shader::Shader()
{

}


Shader::~Shader()
{
	SAFE_RELEASE( _d3dEffect );
}


ShaderPtr Shader::Create()
{
	ShaderPtr shader( new Shader() );

	shader->LoadShader( DEFAULT_SHADER );

	return shader;
}

void Shader::LoadShader( const string& fileName )
{
	LPD3DXBUFFER			error = NULL;
	DWORD					shaderFlags = 0;

	shaderFlags |= D3DXSHADER_DEBUG; // 컴파일러가 디버그 정보를 생성하도록 함

	auto openEffectFile = D3DXCreateEffectFromFile( D3D9_DEVICE, fileName.c_str(), NULL, NULL, shaderFlags, NULL, &_d3dEffect, &error );

	assert( !FAILED( openEffectFile ) );

	if (error)
	{
		error->Release();
	}
}

void Shader::Clear()
{
	SAFE_RELEASE( _d3dEffect );
}