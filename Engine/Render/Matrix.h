#pragma once

class Matrix
{
public:

	Matrix();
	~Matrix();

	inline D3DXMATRIX			Transform();

	inline D3DXMATRIX			Scale(float xpos = 1, float ypos = 1, float zpos = 1);
	inline D3DXMATRIX			Rotate(float xpos = 0, float ypos = 0, float zpos = 0);
	inline D3DXMATRIX			Position(float xpos = 0, float ypos = 0, float zpos = 0);

private:

	D3DXMATRIX					_scale;
	D3DXMATRIX					_rotation;
	D3DXMATRIX					_position;
};

