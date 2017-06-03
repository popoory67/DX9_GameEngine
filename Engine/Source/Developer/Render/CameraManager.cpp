#include "RenderPCH.h"
#include "CameraManager.h"


CameraManager* CameraManager::_instance = nullptr;

CameraManager::CameraManager()
{
}


CameraManager::~CameraManager()
{
	Clear();

	// this is when shared_ptr is not using
	//SAFE_DELETE( _instance );
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

	_cameras.push_back(camera);
}

CameraPtr CameraManager::GetCamera(const int& cameraID) const
{
	return _cameras[cameraID];
}

void CameraManager::Clear()
{
	_cameras.clear();
}