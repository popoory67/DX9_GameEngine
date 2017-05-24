#include "RenderPCH.h"
#include "MeshManager.h"

#include "D3D9Device.h"
#include "CameraManager.h"


MeshManagerPtr MeshManager::_instance = nullptr;

MeshManager::MeshManager()
{
	CameraManager::Get()->AddCamera();
}

MeshManager::~MeshManager()
{
	Clear();
}


MeshManagerPtr MeshManager::Get()
{
	if (!_instance)
	{
		_instance.reset( new MeshManager() );
	}

	return _instance;
}


void MeshManager::AddMesh( const MeshModelPtr mesh )
{
	_models.push_back( mesh );
}

MeshModelPtr MeshManager::GetMesh( const int& id ) const
{
	return _models[id];
}


void MeshManager::Render()
{
	if (_models.size() > 0)
	{
		auto iter = _models.begin();

		while (iter != _models.end())
		{
			(*iter)->Render();

			iter++;
		}
	}
}


void MeshManager::Clear()
{
	_models.clear();
}