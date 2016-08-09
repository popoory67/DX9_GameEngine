#pragma once

#include "Camera.h"

class CameraManager;

using CameraManagerPtr = shared_ptr<CameraManager>; // CameraManager*;
using CameraVector = vector<CameraPtr>;


class CameraManager
{
public:

	~CameraManager();

	static CameraManagerPtr Get();

	void AddCamera();

	CameraPtr GetCamera( const int& cameraID ) const;

private:

	CameraManager();

	void Clear();

private:

	static CameraManagerPtr _instance;

	CameraVector _cameraVector;
	
	int _idCount = 0; // 0 is main camera

};

