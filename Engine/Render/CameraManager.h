#pragma once

#include "Camera.h"

typedef shared_ptr<Camera>		CameraPtr;
typedef vector<CameraPtr>		CameraVector;

class CameraManager
{
public:
	
	~CameraManager();

	static CameraManager& Get();

	void AddCamera();

	CameraPtr GetCamera(const int& cameraID);

private:

	CameraManager();

	void Clear();

private:

	static CameraManager* _instance;

	int _idCount = 0; // 0 is main camera

	CameraVector _cameraVector;

};

