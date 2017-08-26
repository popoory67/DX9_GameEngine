#include "RenderPCH.h"
#include "MeshManager.h"
#include "D3D9Device.h"
#include "CameraManager.h"
#include "Log.h"


MeshManager* MeshManager::_instance = nullptr;

MeshManager::MeshManager()
{
	_models = new MeshModels();

	CameraManager::Get().AddCamera();
}

MeshManager::~MeshManager()
{
	Clear();

	SAFE_DELETE(_models);

	SAFE_DELETE(_instance);
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

//MeshModel* MeshManager::GetMesh( const int id ) const
//{
//	return (*_models)[id];
//}

void MeshManager::RemoveMesh( const int id )
{
	int count = 0;

	for (auto model = _models->begin(); model != _models->end();)
	{
		if (count == id)
		{
			SAFE_DELETE(*model);
			model = _models->erase(model);

			break;
		}

		++count;
		++model;
	}
}

void MeshManager::RemoveMesh(const MeshModel* mesh)
{
	for (auto model = _models->begin(); model != _models->end();)
	{
		if ((*model) == mesh)
		{
			SAFE_DELETE(*model);
			model = _models->erase(model);

			break;
		}

		++model;
	}
}


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
	for (auto model = _models->begin(); model != _models->end();)
	{
		SAFE_DELETE(*model);
		model = _models->erase(model);
	}

	_models->clear();
}