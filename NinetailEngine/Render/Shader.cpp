#include "RenderPCH.h"
#include "CreateDeviceD3DX.h"
#include "Shader.h"


Shader::Shader() : _shader(NULL)
{

}


Shader::~Shader()
{

}


void Shader::Init()
{
	if ((_shader = LoadShader(PHONG_BUMP_REFLECT)) == NULL)
	{
		return;
	}

	if ((_shader = LoadShader(POST_GLOW)) == NULL)
	{
		return;
	}
}


LPD3DXEFFECT Shader::GetShader()
{
	return _shader;
}

LPD3DXEFFECT Shader::LoadShader(string file_name)
{
	LPD3DXEFFECT			ret				= NULL;
	LPD3DXBUFFER			error			= NULL;
	DWORD					shaderFlags		= 0;

	shaderFlags |= D3DXSHADER_DEBUG;

	if (FAILED(D3DXCreateEffectFromFile(D3DX_DEVICE, file_name.c_str(), NULL, NULL, shaderFlags, NULL, &ret, &error)))
	{
		MessageBox(NULL, "failed fx file loading", "ninetail rendering engine", MB_OK);
	}

	if (!ret && error)
	{
		int		size	= error->GetBufferSize();
		void*	ack		= error->GetBufferPointer();

		if (ack)
		{
			char* str = new char[size];

			sprintf_s(str, size, (const char*)ack);
			OutputDebugString(str);

			delete[] str;
		}
	}

	return ret; 
}