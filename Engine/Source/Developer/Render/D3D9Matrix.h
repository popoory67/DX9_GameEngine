#pragma once

#include <d3dx9.h>

class D3D9Matrix;

using D3D9MatrixPtr = shared_ptr<D3D9Matrix>;

class D3D9Matrix
{
public:

	D3D9Matrix();
	~D3D9Matrix();

	static D3D9MatrixPtr Create();

	D3DXMATRIX Transform();

	D3DXMATRIX Scale(float xpos = 1, float ypos = 1, float zpos = 1);
	D3DXMATRIX Rotate(float xpos = 0, float ypos = 0, float zpos = 0);
	D3DXMATRIX Position(float xpos = 0, float ypos = 0, float zpos = 0);

private:

	D3DXMATRIX _scale;
	D3DXMATRIX _rotation;
	D3DXMATRIX _position;
};

