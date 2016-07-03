#pragma once

#include "XMeshObject.h"
#include "ObjMeshObject.h"

#define GET_MESH(id)	MeshManager::Get().GetMesh(id)

using XMeshObjectPtr = shared_ptr< XMeshObject >;
using XMeshVector = vector< XMeshObjectPtr >;

using ObjMeshObjectPtr = shared_ptr< ObjMeshObject >;
using ObjMeshVector = vector< ObjMeshObjectPtr >;


class MeshManager
{
public:

	~MeshManager();

	// singleton
	static MeshManager& Get();

public:

	// get .obj vector
	ObjMeshVector GetObjVector() const { return _objVector; }

	// get .x vector
	XMeshVector GetXVector() const { return _xVector; }

	// add .x file mesh
	void AddMesh( XMeshObjectPtr mesh );

	// add .obj file mesh
	void AddMesh( ObjMeshObjectPtr mesh );

	// get .obj mesh
	ObjMeshObjectPtr GetMesh( const int& id ) const;

public:

	void Init();

	void Render();

	void Clear();

private:

	MeshManager();

	void XFileRender();

	void ObjFileRender();

private:

	static MeshManager* _instance;

	XMeshVector _xVector;
	ObjMeshVector _objVector;
};
