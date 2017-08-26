#pragma once

#include "MeshModel.h"

#define GET_MESH(id)	MeshManager::Get()->GetMesh(id)


class MeshManager
{
	using MeshModels = list<MeshModel*>;

public:

	~MeshManager();

	static MeshManager&		Get();

public:

	//MeshModel*		GetMesh( const int id ) const;
	
	void			AddMesh( MeshModel* mesh );

	void			RemoveMesh( const int id );
	void			RemoveMesh( const MeshModel* mesh );

	void			Render();

private:

	MeshManager();

	void			Clear();

private:

	static MeshManager*		_instance;

	MeshModels*				_models;
};
