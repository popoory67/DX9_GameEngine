#include "RenderPCH.h"
#include "Matrix.h"


Matrix::Matrix()
{
	D3DXMatrixIdentity(&_scale);
	D3DXMatrixIdentity(&_rotation);
	D3DXMatrixIdentity(&_position);
}


Matrix::~Matrix()
{
}


D3DXMATRIX Matrix::Transform()
{
	D3DXMATRIX worldMatrix;

	worldMatrix = _scale * _rotation * _position;

	return worldMatrix;
}


D3DXMATRIX Matrix::Scale(float xpos, float ypos, float zpos)
{
	D3DXMatrixScaling(&_scale, xpos, ypos, zpos);

	return _scale;
}

D3DXMATRIX Matrix::Rotate(float xpos, float ypos, float zpos)
{
	// rotation function

	return _rotation;
}

D3DXMATRIX Matrix::Position(float xpos, float ypos, float zpos)
{
	D3DXMatrixTranslation(&_position, xpos, ypos, zpos);

	return _position;
}