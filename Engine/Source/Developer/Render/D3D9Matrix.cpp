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