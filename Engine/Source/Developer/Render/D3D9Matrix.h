#pragma once

#include <d3dx9.h>
#include "Matrix.h"

class D3D9Matrix;

using D3D9MatrixPtr = shared_ptr<D3D9Matrix>;

class D3D9Matrix : public Matrix<D3DXMATRIX>
{
private:
	using D3D9MatrixType = Matrix<D3DXMATRIX>::Type;

public:

	D3D9Matrix();
	~D3D9Matrix();

	static D3D9MatrixPtr Create();

	virtual D3D9MatrixType Transform()
	{
		D3DXMATRIX worldMatrix;

		worldMatrix = _scale * _rotation * _position;

		return worldMatrix;
	}

	virtual D3D9MatrixType SetScale( float xpos = 1, float ypos = 1, float zpos = 1 )
	{
		D3DXMatrixScaling( &_scale, xpos, ypos, zpos );

		return _scale;
	}
	
	virtual D3D9MatrixType SetRotate( float xpos = 0, float ypos = 0, float zpos = 0 )
	{
		if (xpos != 0)
		{
			D3DXVECTOR3 v( 1, 0, 0 );
			//D3DXMatrixRotationAxis( &_rotation, &v, xpos );
			D3DXMatrixRotationX( &_rotation, xpos );
		}

		if (ypos != 0)
		{
			D3DXVECTOR3 v( 0, 1, 0 );
			D3DXMatrixRotationY( &_rotation, ypos );
			//D3DXMatrixRotationAxis( &_rotation, &v, ypos );
		}

		if (zpos != 0)
		{
			D3DXVECTOR3 v( 0, 0, 1 );
			//D3DXMatrixRotationAxis( &_rotation, &v, zpos );
			D3DXMatrixRotationZ( &_rotation, zpos );
		}

		//D3DXMatrixRotationYawPitchRoll( &_rotation, xpos, ypos, zpos );

		return _rotation;
	}
	
	virtual D3D9MatrixType SetPosition( float xpos = 0, float ypos = 0, float zpos = 0 )
	{
		D3DXMatrixTranslation( &_position, xpos, ypos, zpos );

		return _position;
	}

private:

	D3DXMATRIX _scale;
	D3DXMATRIX _rotation;
	D3DXMATRIX _position;
};

