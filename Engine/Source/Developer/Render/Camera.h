#pragma once

#include "CreateD3D9.h"

#define FOV				( D3DX_PI/4.0f ) // 시야각
#define ASPECT_RATIO	( SCREEN_WIDTH/(float)SCREEN_HEIGHT ) // 화면의 종횡비
#define NEAR_PLANE		1		// 근접 평면
#define FAR_PLANE		100000	// 원거리 평면

class Camera;

using CameraPtr = shared_ptr<Camera>;

class Camera
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

	void Init();

	void SetRotate();

	void SetPosition( float x = 0, float y = 0, float z = 0 );

	const int GetID() const { return _id; }

	void SetID( int id ) { _id = id; }

private:

	int _id = 0;

	D3DXMATRIXA16 _world;
	D3DXMATRIXA16 _view;
	D3DXMATRIXA16 _proj;

	D3DXVECTOR3 _eyePt;
	D3DXVECTOR3 _lookAtPt;
	D3DXVECTOR3 _upVec;
};
