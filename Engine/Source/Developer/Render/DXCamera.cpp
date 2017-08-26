#include "RenderPCH.h"
#include "DXCamera.h"


DXCamera::DXCamera()
{

}

DXCamera::~DXCamera()
{

}

CameraPtr DXCamera::Create()
{
	CameraPtr camera( new DXCamera() );

	camera->Init();

	return camera;
}

void DXCamera::Init()
{
	// world
	D3DXMatrixIdentity( &_world );

	// view
	_eyeVec = D3DXVECTOR3( 0.0f, 50, -70 ); // camera position
	_lookVec = D3DXVECTOR3( 0.0f, 30.0f, 0.0f ); // look at point
	_upVec = D3DXVECTOR3( 0.0f, 1.0f, 0.0f );

	D3DXMatrixLookAtLH( &_view, &_eyeVec, &_lookVec, &_upVec );

	// projection
	D3DXMatrixPerspectiveFovLH( &_proj, FOV, 1.0f, NEAR_PLANE, FAR_PLANE );

	// transform camera
	D3D9_DEVICE->SetTransform( D3DTS_WORLD, &_world );
	D3D9_DEVICE->SetTransform( D3DTS_VIEW, &_view );
	D3D9_DEVICE->SetTransform( D3DTS_PROJECTION, &_proj );
}

void DXCamera::SetRotate( float x, float y, float z )
{
	SetRotate( &D3DXVECTOR3( x, y, z ), 1 );
}

void DXCamera::SetRotate( const D3DXVECTOR3* deltaVec, float speed )
{
	D3DXVECTOR3 epsilonVec = *deltaVec;

	float yaw;
	float pitch;

	D3DXVECTOR3 xVec;
	D3DXVECTOR3 yVec;
	D3DXVECTOR3 zVec;

	D3DXMATRIX rtY;
	D3DXMATRIX rtX;

	// 월드 좌표 y 축에 대한 회전
	yaw = D3DXToRadian( epsilonVec.x * speed );
	D3DXMatrixRotationY( &rtY, yaw );

	zVec = _lookVec - _eyeVec;
	yVec = D3DXVECTOR3( _view._12, _view._22, _view._32 );

	D3DXVec3TransformCoord( &zVec, &zVec, &rtY );
	D3DXVec3TransformCoord( &yVec, &yVec, &rtY );

	_lookVec = zVec + _eyeVec;
	_upVec = yVec;
	D3DXMatrixLookAtLH( &_view, &_eyeVec, &_lookVec, &_upVec );

	// 카메라의 x 축에 대한 회전
	pitch = D3DXToRadian( epsilonVec.y * speed );
	xVec = D3DXVECTOR3( _view._11, _view._21, _view._31 );
	yVec = D3DXVECTOR3( _view._12, _view._22, _view._32 );
	zVec = _lookVec - _eyeVec;

	D3DXMatrixRotationAxis( &rtX, &xVec, pitch );
	D3DXVec3TransformCoord( &zVec, &zVec, &rtX );
	D3DXVec3TransformCoord( &yVec, &yVec, &rtX );

	_lookVec = zVec + _eyeVec;
	_upVec = yVec;
	D3DXMatrixLookAtLH( &_view, &_eyeVec, &_lookVec, &_upVec );
}

void DXCamera::SetPosition( float x /* = 0 */, float y /* = 0 */, float z /* = 0 */ )
{
	_eyeVec += D3DXVECTOR3( x, y, z );

	SetTransform();
}

void DXCamera::SetTransform()
{
	D3DXMatrixLookAtLH( &_view, &_eyeVec, &_lookVec, &_upVec );
	D3D9_DEVICE->SetTransform( D3DTS_VIEW, &_view );
	D3D9_DEVICE->SetTransform( D3DTS_PROJECTION, &_proj );
}

void DXCamera::MoveForward( float	speed, float y )
{
	D3DXVECTOR3 zVec( _view._13, _view._23 * y, _view._33 );
	D3DXVec3Normalize( &zVec, &zVec );

	_eyeVec += zVec * speed;
	_lookVec += zVec * speed;
}

void DXCamera::MoveSideward( float speed )
{
	D3DXVECTOR3 xVec( _view._11, 0, _view._31 );
	D3DXVec3Normalize( &xVec, &xVec );

	_eyeVec += xVec * speed;
	_lookVec += xVec * speed;
}