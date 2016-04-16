#pragma once

#include "RenderPCH.h"
#include "CreateDeviceD3DX.h"


class Shader
{
private:

public:
	Shader();
	~Shader();

	LPD3DXEFFECT				LoadShader(string file_name);
};

