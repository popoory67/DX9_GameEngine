#pragma once

#define DEFAULT_SHADER			"C:/Users/boseul/Documents/GitHub/NinetailEngine/Engine/Resource/ObjViewer.fx"

typedef function<void()>		FuncVoid;

class Shader
{
public:
	Shader();
	~Shader();

	static Shader* Create();

	LPD3DXEFFECT GetEffect() { return _d3dEffect; }

	FuncVoid GetShaderFunc() { return _shaderFunc; }

	void SetShaderFunc(FuncVoid func) { _shaderFunc = func; }

public:

	void LoadShader(const string& fileName);

	void Clear();

private:

	LPD3DXEFFECT _d3dEffect = nullptr;

	FuncVoid _shaderFunc = nullptr;

};

