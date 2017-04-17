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
	virtual ~D3D9Matrix();

	static D3D9MatrixPtr Create();

	virtual D3D9MatrixType Transform()
	{
		D3DXMATRIX world;

		world = _scale * _rotation * _position * _world;

		return world;
	}

	virtual D3D9MatrixType SetWorld( D3DXMATRIX world )
	{
		_world = world;

		return _world;
	}

	virtual D3D9MatrixType SetScale( float xpos = 1, float ypos = 1, float zpos = 1 )
	{
		D3DXMatrixScaling( &_scale, xpos, ypos, zpos );

		return _scale;
	}

	virtual D3D9MatrixType SetScale( D3DXMATRIX scale )
	{
		_scale = scale;

		return _scale;
	}

	virtual D3D9MatrixType SetRotate( float xpos = 0, float ypos = 0, float zpos = 0 )
	{
		D3DXMatrixRotationYawPitchRoll( &_rotation, ypos, xpos, zpos );

		return _rotation;
	}

	virtual D3D9MatrixType SetRotate( D3DXMATRIX rotation )
	{
		_rotation = rotation;

		return _rotation;
	}

	virtual D3D9MatrixType SetPosition( float xpos = 0, float ypos = 0, float zpos = 0 )
	{
		D3DXMatrixTranslation( &_position, xpos, ypos, zpos );

		return _position;
	}

	virtual D3D9MatrixType SetPosition( D3DXMATRIX position )
	{
		_position = position;

		return _position;
	}

private:

	D3DXMATRIX _world;

	D3DXMATRIX _scale;
	D3DXMATRIX _rotation;
	D3DXMATRIX _position;
};

