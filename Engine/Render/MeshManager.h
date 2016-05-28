#pragma once

#include "XMeshObject.h"
#include "ObjMeshObject.h"

#define GET_MESH(id)	MeshManager::Get().GetMesh(id)

typedef shared_ptr<XMeshObject>			XMeshObjectPtr;
typedef vector< XMeshObjectPtr >		XMeshVector;

typedef shared_ptr<ObjMeshObject>		ObjMeshObjectPtr;
typedef vector< ObjMeshObjectPtr >		ObjMeshVector;


class MeshManager
{
public:

	~MeshManager();

	// singleton
	static MeshManager& Get();

public:

	// get .obj vector
	ObjMeshVector GetObjVector() { return _objVector; }

	// get .x vector
	XMeshVector GetXVector() { return _xVector; }

	// add .x file mesh
	void AddMesh(XMeshObjectPtr mesh);

	// add .obj file mesh
	void AddMesh(ObjMeshObjectPtr mesh);

	// get .obj mesh
	ObjMeshObjectPtr GetMesh(const int& id);

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
