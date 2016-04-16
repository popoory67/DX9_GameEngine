#include "RenderPCH.h"
#include "Shader.h"


Shader::Shader()
{
}


Shader::~Shader()
{
}


LPD3DXEFFECT Shader::LoadShader(string file_name)
{
	LPD3DXEFFECT			ret				= NULL;
	LPD3DXBUFFER			error			= NULL;
	DWORD					shaderFlags		= 0;

	shaderFlags |= D3DXSHADER_DEBUG;

	D3DXCreateEffectFromFile(D3DX_DEVICE, file_name.c_str(), NULL, NULL, shaderFlags, NULL, &ret, &error);

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