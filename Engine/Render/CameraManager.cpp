#include "RenderPCH.h"
#include "CameraManager.h"


CameraManager* CameraManager::_instance = nullptr;

CameraManager::CameraManager()
{
}


CameraManager::~CameraManager()
{
	Clear();

	if (_instance)
	{
		SAFE_DELETE(_instance);
	}
}


CameraManager& CameraManager::Get()
{
	if (!_instance)
	{
		_instance = new CameraManager();
	}

	return *_instance;
}

void CameraManager::AddCamera()
{
	CameraPtr camera(Camera::Create());

	camera->SetID(_idCount);

	_cameraVector.push_back(camera);
}

CameraPtr CameraManager::GetCamera(const int& cameraID)
{
	return _cameraVector[cameraID];
}

void CameraManager::Clear()
{
	_cameraVector.clear();
}