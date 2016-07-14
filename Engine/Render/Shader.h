#pragma once

#define DEFAULT_SHADER			"C:/Users/boseul/Documents/GitHub/NinetailEngine/Engine/Resource/ObjViewer.fx"

class Shader;

using ShaderPtr = shared_ptr<Shader>;
using FuncVoid = function<void()>;

class Shader
{
public:
	Shader();
	~Shader();

	static ShaderPtr Create();

	LPD3DXEFFECT GetEffect() const { return _d3dEffect; }

	FuncVoid GetShaderFunc() const { return _shaderFunc; }

	void SetShaderFunc(FuncVoid func) { _shaderFunc = func; }

public:

	void LoadShader(const string& fileName);

	void Clear();

private:

	LPD3DXEFFECT _d3dEffect = nullptr;

	FuncVoid _shaderFunc = nullptr;

};

