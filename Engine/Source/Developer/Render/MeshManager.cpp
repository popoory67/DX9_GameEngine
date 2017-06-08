#include "RenderPCH.h"
#include "MeshManager.h"
#include "D3D9Device.h"
#include "CameraManager.h"
#include "Log.h"


MeshManager::MeshManager()
{
	_models = new MeshModels();

	CameraManager::Get().AddCamera();
}

MeshManager::~MeshManager()
{
	Clear();
}


MeshManager& MeshManager::Get()
{
	if (!_instance)
	{
		_instance = new MeshManager();
	}

	return *_instance;
}


void MeshManager::AddMesh( MeshModel* mesh )
{
	_models->push_back( mesh );
}

//MeshModel* MeshManager::GetMesh( const int& id ) const
//{
//	return _models[id];
//}


void MeshManager::Render()
{
	if (!_models->empty())
	{
		int size	= _models->size();

		for (auto iter = _models->begin(); iter != _models->end(); iter++)
		{
			(*iter)->Render();
		}
	}
}


void MeshManager::Clear()
{
	_models->clear();
}