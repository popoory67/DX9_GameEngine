#pragma once

#include <d3dx9.h>
#include "Matrix.h"

class D3D9Matrix;

using D3D9MatrixPtr			= shared_ptr<D3D9Matrix>;
using D3D9MatrixType		= Matrix<D3DXMATRIX>::Type;

class D3D9Matrix : public Matrix<D3DXMATRIX>
{

public:

	D3D9Matrix();
	virtual ~D3D9Matrix();

	static D3D9MatrixPtr	Create();

	virtual D3D9MatrixType	Transform();

	virtual D3D9MatrixType	SetWorld(D3DXMATRIX world);

	virtual D3D9MatrixType	SetScale(float xpos = 1, float ypos = 1, float zpos = 1);
	virtual D3D9MatrixType	SetScale(D3DXMATRIX scale);

	virtual D3D9MatrixType	SetRotate(float xpos = 0, float ypos = 0, float zpos = 0);
	virtual D3D9MatrixType	SetRotate(D3DXMATRIX rotation);

	virtual D3D9MatrixType	SetPosition(float xpos = 0, float ypos = 0, float zpos = 0);
	virtual D3D9MatrixType	SetPosition(D3DXMATRIX position);

private:

	D3DXMATRIX		_world;

	D3DXMATRIX		_scale;
	D3DXMATRIX		_rotation;
	D3DXMATRIX		_position;
};

