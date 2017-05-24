#pragma once

#include "MeshModel.h"

#define GET_MESH(id)	MeshManager::Get()->GetMesh(id)

class MeshManager;

using MeshManagerPtr = shared_ptr<MeshManager>; // MeshManager*;


class MeshManager
{
	using MeshModels = vector<MeshModelPtr>;

public:

	~MeshManager();

	// singleton
	static MeshManagerPtr Get();

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

	static MeshManagerPtr _instance;

	MeshModels _models;
};
