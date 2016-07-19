#pragma once

#include "MeshModel.h"

#define GET_MESH(id)	MeshManager::Get().GetMesh(id)

using MeshVector = vector< MeshModelPtr >;

class MeshManager
{
public:

	~MeshManager();

	// singleton
	static MeshManager& Get();

public:

	MeshModelPtr GetMesh( const int& id ) const;

	// add mesh
	void AddMesh( const MeshModelPtr mesh );

public:

	void Render();

	void Clear();

private:

	MeshManager();

private:

	static MeshManager* _instance;

	MeshVector _meshVector;
};
