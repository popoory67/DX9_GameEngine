#include "RenderPCH.h"
#include "D3D9Matrix.h"


D3D9Matrix::D3D9Matrix()
{
	D3DXMatrixIdentity( &_world );
	D3DXMatrixIdentity( &_scale );
	D3DXMatrixIdentity( &_rotation );
	D3DXMatrixIdentity( &_position );
}


D3D9Matrix::~D3D9Matrix()
{

}


D3D9MatrixPtr D3D9Matrix::Create()
{
	D3D9MatrixPtr matrix( new D3D9Matrix() );

	return matrix;
}


D3D9MatrixType D3D9Matrix::Transform()
{
	D3DXMATRIX world;

	world = _scale * _rotation * _position * _world;

	return world;
}

D3D9MatrixType D3D9Matrix::SetWorld(D3DXMATRIX world)
{
	_world = world;

	return _world;
}

D3D9MatrixType D3D9Matrix::SetScale(float xpos, float ypos, float zpos)
{
	D3DXMatrixScaling(&_scale, xpos, ypos, zpos);

	return _scale;
}

D3D9MatrixType D3D9Matrix::SetScale(D3DXMATRIX scale)
{
	_scale = scale;

	return _scale;
}

D3D9MatrixType D3D9Matrix::SetRotate(float xpos, float ypos, float zpos)
{
	D3DXMatrixRotationYawPitchRoll(&_rotation, ypos, xpos, zpos);

	return _rotation;
}

D3D9MatrixType D3D9Matrix::SetRotate(D3DXMATRIX rotation)
{
	_rotation = rotation;

	return _rotation;
}

D3D9MatrixType D3D9Matrix::SetPosition(float xpos, float ypos, float zpos)
{
	D3DXMatrixTranslation(&_position, xpos, ypos, zpos);

	return _position;
}

D3D9MatrixType D3D9Matrix::SetPosition(D3DXMATRIX position)
{
	_position = position;

	return _position;
}