#pragma once

#include <d3dx9.h>
#include <functional>
#include "D3DXShader.h"


class D3D9Shader;

using ShaderPtr		= shared_ptr<D3D9Shader>;
using FuncVoid		= function<void()>;

class D3D9Shader : public D3DXShader
{
public:
	D3D9Shader();
	virtual ~D3D9Shader();

	static ShaderPtr	Create();

	LPD3DXEFFECT		GetEffect() const					{ return _d3dEffect; }

	FuncVoid			GetShaderFunc() const				{ return _shaderFunc; }

	void				SetShaderFunc( FuncVoid func )		{ _shaderFunc = func; }

	virtual void		LoadShader( const string& fileName );

private:

	LPD3DXEFFECT	_d3dEffect		= nullptr;

	FuncVoid		_shaderFunc		= nullptr;

};

