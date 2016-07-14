#pragma once

class Matrix;

using MatrixPtr = shared_ptr<Matrix>;

class Matrix
{
public:

	Matrix();
	~Matrix();

	static MatrixPtr Create();

	D3DXMATRIX Transform();

	D3DXMATRIX Scale(float xpos = 1, float ypos = 1, float zpos = 1);
	D3DXMATRIX Rotate(float xpos = 0, float ypos = 0, float zpos = 0);
	D3DXMATRIX Position(float xpos = 0, float ypos = 0, float zpos = 0);

private:

	D3DXMATRIX _scale;
	D3DXMATRIX _rotation;
	D3DXMATRIX _position;
};

