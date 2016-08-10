#include "RenderPCH.h"
#include "Camera.h"


Camera::Camera()
{

}

Camera::~Camera()
{

}

CameraPtr Camera::Create()
{
	CameraPtr camera( new Camera() );

	camera->Init();

	return camera;
}

void Camera::Init()
{
	// world
	//D3DXMatrixRotationY(&_world, timeGetTime() / 1000.0f);
	D3DXMatrixIdentity( &_world );

	// view
	_eyePt = D3DXVECTOR3( 0.0f, 79, -70 ); // camera position
	_lookAtPt = D3DXVECTOR3( 0.0f, 0.0f, 0.0f ); // look at point
	_upVec = D3DXVECTOR3( 0.0f, 1.0f, 0.0f );

	D3DXMatrixLookAtLH( &_view, &_eyePt, &_lookAtPt, &_upVec );

	// projection
	D3DXMatrixPerspectiveFovLH( &_proj, FOV, 1.0f, NEAR_PLANE, FAR_PLANE );

	// transform camera
	D3D9_DEVICE->SetTransform( D3DTS_WORLD, &_world );
	D3D9_DEVICE->SetTransform( D3DTS_VIEW, &_view );
	D3D9_DEVICE->SetTransform( D3DTS_PROJECTION, &_proj );
}

void Camera::SetRotate()
{

}

void Camera::SetPosition( float x /* = 0 */, float y /* = 0 */, float z /* = 0 */ )
{
	_eyePt += D3DXVECTOR3( x, y, z );

	D3DXMatrixLookAtLH( &_view, &_eyePt, &_lookAtPt, &_upVec );
	D3D9_DEVICE->SetTransform( D3DTS_VIEW, &_view );
	D3D9_DEVICE->SetTransform( D3DTS_PROJECTION, &_proj );
}