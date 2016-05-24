#include "RenderPCH.h"
#include "Shader.h"

#include "CreateD3D9.h"

Shader::Shader() : _effect(nullptr)
{
	Init();
}


Shader::~Shader()
{
	Clear();
}


void Shader::Init()
{
	LoadShader(DEFAULT_SHADER);
}


void Shader::LoadShader(const string& fileName)
{
	LPD3DXBUFFER			error			= NULL;
	DWORD					shaderFlags		= 0;

	shaderFlags |= D3DXSHADER_DEBUG; // �����Ϸ��� ����� ������ �����ϵ��� ��

	if (FAILED(D3DXCreateEffectFromFile(D3D9_DEVICE, fileName.c_str(), NULL, NULL, shaderFlags, NULL, &_effect, &error)))
	{
		MessageBox(NULL, "failed fx file loading", "ninetail rendering engine", MB_OK);

		if (error)
		{
			error->Release();
		}
	}

}

void Shader::Clear()
{
	SAFE_RELEASE(_effect);
}