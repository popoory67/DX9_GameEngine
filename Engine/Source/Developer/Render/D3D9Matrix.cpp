#include "RenderPCH.h"
#include "D3D9Matrix.h"


D3D9Matrix::D3D9Matrix()
{
	D3DXMatrixIdentity(&_scale);
	D3DXMatrixIdentity(&_rotation);
	D3DXMatrixIdentity(&_position);
}


D3D9Matrix::~D3D9Matrix()
{

}

D3D9MatrixPtr D3D9Matrix::Create()
{
	D3D9MatrixPtr matrix( new D3D9Matrix() );

	return matrix;
}

D3DXMATRIX D3D9Matrix::Transform()
{
	D3DXMATRIX worldMatrix;

	worldMatrix = _scale * _rotation * _position;

	return worldMatrix;
}


D3DXMATRIX D3D9Matrix::Scale( float xpos, float ypos, float zpos )
{
	D3DXMatrixScaling(&_scale, xpos, ypos, zpos);

	return _scale;
}

D3DXMATRIX D3D9Matrix::Rotate( float xpos, float ypos, float zpos )
{
	if (xpos != 0)
	{
		D3DXVECTOR3 v( 1, 0, 0 );
		D3DXMatrixRotationAxis( &_rotation, &v, xpos );
	}

	if (ypos != 0)
	{
		D3DXVECTOR3 v( 0, 1, 0 );
		D3DXMatrixRotationAxis( &_rotation, &v, ypos );
	}

	if (zpos != 0)
	{
		D3DXVECTOR3 v( 0, 0, 1 );
		D3DXMatrixRotationAxis( &_rotation, &v, zpos );
	}

	//D3DXMatrixRotationYawPitchRoll( &_rotation, xpos, ypos, zpos );

	return _rotation;
}

D3DXMATRIX D3D9Matrix::Position( float xpos, float ypos, float zpos )
{
	D3DXMatrixTranslation(&_position, xpos, ypos, zpos);

	return _position;
}