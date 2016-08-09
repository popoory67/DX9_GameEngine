#include "RenderPCH.h"
#include "CameraManager.h"


CameraManagerPtr CameraManager::_instance = nullptr;

CameraManager::CameraManager()
{
}


CameraManager::~CameraManager()
{
	Clear();

	// this is when shared_ptr is not using
	//SAFE_DELETE( _instance );
}


CameraManagerPtr CameraManager::Get()
{
	if (!_instance)
	{
		_instance.reset( new CameraManager() ); // = new CameraManager();
	}

	return _instance;
}

void CameraManager::AddCamera()
{
	CameraPtr camera(Camera::Create());

	camera->SetID(_idCount);

	_cameraVector.push_back(camera);
}

CameraPtr CameraManager::GetCamera(const int& cameraID) const
{
	return _cameraVector[cameraID];
}

void CameraManager::Clear()
{
	_cameraVector.clear();
}