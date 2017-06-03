#pragma once

#include "D3D9Device.h"
#include "ICamera.h"

class Camera;

using CameraPtr = shared_ptr<Camera>;

class Camera : public ICamera
{
private:

	struct CameraMatrix
	{
		D3DXMATRIXA16 _world;
		D3DXMATRIXA16 _view;
		D3DXMATRIXA16 _proj;
	};

	struct CameraVector
	{
		D3DXVECTOR3 _eyeVec;
		D3DXVECTOR3 _lookVec;
		D3DXVECTOR3 _upVec;
	};

public:

	Camera();
	virtual ~Camera();

	static CameraPtr		Create();

	const CameraMatrix&		GetCameraMatrix() const
	{
		CameraMatrix* mat = new CameraMatrix();

		mat->_world = _world;
		mat->_view = _view;
		mat->_proj = _proj;

		return *mat;
	}

	const CameraVector&		GetCameraVector() const
	{
		CameraVector* vec = new CameraVector();

		vec->_eyeVec = _eyeVec;
		vec->_lookVec = _lookVec;
		vec->_upVec = _upVec;

		return *vec;
	}

	virtual void	Init();

	virtual void	SetRotate( float x = 0, float y = 0, float z = 0 );

	virtual void	SetRotate( const D3DXVECTOR3* deltaVec, float speed );

	virtual void	SetPosition( float x = 0, float y = 0, float z = 0 );

	virtual void	 SetTransform();

	void		MoveSideward( float speed );

	void		MoveForward( float	speed, float y = 0 );

private:

	D3DXMATRIXA16	_world;
	D3DXMATRIXA16	_view;
	D3DXMATRIXA16	_proj;

	D3DXVECTOR3		_eyeVec;
	D3DXVECTOR3		_lookVec;
	D3DXVECTOR3		_upVec;
};
