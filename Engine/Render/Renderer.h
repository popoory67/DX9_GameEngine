#pragma once

#include "Camera.h"
#include "XMeshObject.h"
#include "ObjMeshObject.h"

typedef SHARED_PTR(XMeshObject)					XMeshObjectPtr;
typedef vector< XMeshObjectPtr >				XMeshVector;

typedef ObjMeshObject*							ObjMeshObjectPtr;
typedef vector< ObjMeshObjectPtr >				ObjMeshVector;


class Renderer
{
public:

	~Renderer();

	// singleton
	static Renderer& Get();

	// Add X file mesh
	void AddMesh(XMeshObjectPtr mesh);

	// Add Obj file mesh
	void AddMesh(ObjMeshObjectPtr mesh);

	void Init();

	void Render();

	void Clear();

private:

	Renderer();

	void XFileRender();

	void ObjFileRender();

private:

	static Renderer* _instance;

	Camera*	_mainCamera;

	XMeshVector* _xMesh;
	ObjMeshVector* _objMesh;

};
