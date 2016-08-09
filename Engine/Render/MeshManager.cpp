#include "RenderPCH.h"
#include "MeshManager.h"

#include "CreateD3D9.h"
//#include "CreateD3D11.h"
#include "CameraManager.h"


MeshManagerPtr MeshManager::_instance = nullptr;

MeshManager::MeshManager()
{
	CameraManager::Get()->AddCamera();
}

MeshManager::~MeshManager()
{
	Clear();

	//SAFE_DELETE( _instance );
}


MeshManagerPtr MeshManager::Get()
{
	if (!_instance)
	{
		_instance.reset( new MeshManager() ); //= new MeshManager();
	}

	return _instance;
}


void MeshManager::AddMesh( const MeshModelPtr mesh )
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