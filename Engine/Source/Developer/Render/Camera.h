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

		D3DXVECTOR3 _eyePt;
		D3DXVECTOR3 _lookAtPt;
		D3DXVECTOR3 _upVec;
	};

public:

	Camera();
	~Camera();

	static CameraPtr Create();

	const CameraMatrix* GetCameraMatrix() const
	{
		CameraMatrix* mat = new CameraMatrix();

		mat->_world = _world;
		mat->_view = _view;
		mat->_proj = _proj;

		mat->_eyePt = _eyePt;
		mat->_lookAtPt = _lookAtPt;
		mat->_upVec = _upVec;

		return mat;
	}

	virtual void Init();

	virtual void SetRotate();

	virtual void SetPosition( float x = 0, float y = 0, float z = 0 );

private:

	D3DXMATRIXA16 _world;
	D3DXMATRIXA16 _view;
	D3DXMATRIXA16 _proj;

	D3DXVECTOR3 _eyePt;
	D3DXVECTOR3 _lookAtPt;
	D3DXVECTOR3 _upVec;
};
