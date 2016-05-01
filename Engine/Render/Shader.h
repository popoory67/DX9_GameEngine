#pragma once


class Shader
{
private:

	LPD3DXEFFECT				_shader;

public:
	Shader();
	~Shader();

	void						Init();

	LPD3DXEFFECT				GetShader();

	LPD3DXEFFECT				LoadShader(string file_name);
};

