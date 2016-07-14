#include "RenderPCH.h"
#include "MeshManager.h"

#include "CreateD3D9.h"
//#include "CreateD3D11.h"
#include "CameraManager.h"


MeshManager* MeshManager::_instance = nullptr;

MeshManager::MeshManager()
{
	CameraManager::Get().AddCamera();
}

MeshManager::~MeshManager()
{
	Clear();

	SAFE_DELETE( _instance );
}


MeshManager& MeshManager::Get()
{
	if (!_instance)
	{
		_instance = new MeshManager();
	}

	return *_instance;
}


void MeshManager::AddMesh( MeshModelPtr mesh )
{
	_meshVector.push_back( mesh );
}


MeshModelPtr MeshManager::GetMesh( const int& id ) const
{
	return _meshVector[id];
}


void MeshManager::Render()
{
	if (_meshVector.size() > 0)
	{
		auto iter = _meshVector.begin();

		while (iter != _meshVector.end())
		{
			(*iter)->Render();

			iter++;
		}
	}
}


void MeshManager::Clear()
{
	_meshVector.clear();
}