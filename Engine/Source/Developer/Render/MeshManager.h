#pragma once

#include "MeshModel.h"

#define GET_MESH(id)	MeshManager::Get()->GetMesh(id)


class MeshManager
{
	using MeshModels = vector<MeshModelPtr>;

public:

	~MeshManager();

	// singleton
	static MeshManager& Get();

public:

	MeshModelPtr	GetMesh( const int& id ) const;
	void			AddMesh( const MeshModelPtr mesh );

	void	Render();

	void	Clear();

private:

	MeshManager();

private:

	static MeshManager*		_instance;

	MeshModels				_models;
};
