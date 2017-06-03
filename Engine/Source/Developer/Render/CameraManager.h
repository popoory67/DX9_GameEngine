#pragma once

#include "Camera.h"

using Cameras		= vector<CameraPtr>;

class CameraManager
{
public:

	~CameraManager();

	static CameraManager&	Get();

	void		AddCamera();

	CameraPtr	GetCamera( const int& cameraID ) const;

private:

	CameraManager();

	void		Clear();

private:

	static CameraManager*	_instance;

	Cameras		_cameras;
	
	int			_idCount		= 0; // 0 is main camera

};

