#pragma once

#include "Camera.h"

class CameraManager;

using CameraVector = vector<CameraPtr>;

class CameraManager
{
public:
	
	~CameraManager();

	static CameraManager& Get();

	void AddCamera();

	CameraPtr GetCamera(const int& cameraID) const;

private:

	CameraManager();

	void Clear();

private:

	static CameraManager* _instance;

	int _idCount = 0; // 0 is main camera

	CameraVector _cameraVector;

};

