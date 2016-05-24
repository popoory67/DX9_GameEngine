#pragma once

#define DEFAULT_SHADER		"C:/Users/boseul/Documents/GitHub/NinetailEngine/Engine/Resource/ObjViewer.fx"


class Shader
{
public:
	Shader();
	~Shader();

	LPD3DXEFFECT GetEffect() { return _effect; }

	void Init();

	void LoadShader(const string& fileName);

	void Clear();

private:

	LPD3DXEFFECT _effect;

};

