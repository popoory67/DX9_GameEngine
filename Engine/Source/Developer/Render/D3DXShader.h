#pragma once

#define DEFAULT_SHADER			"C:/Users/boseul/Documents/GitHub/NinetailEngine/Resource/ObjViewer.fx"

class D3DXShader
{
public:
	D3DXShader();
	virtual ~D3DXShader();

	virtual void	LoadShader(const string& fileName);
};

