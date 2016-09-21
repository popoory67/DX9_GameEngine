#pragma once

#include "ObjLoader.h"
#include "MeshModel.h"

using namespace ObjLoader;

class ObjMeshObject;

using ObjMeshPtr = shared_ptr<ObjMeshObject>;
using Float3 = ObjMesh::Float3;
using Float2 = ObjMesh::Float2;

class ObjMeshObject : public MeshModel
{
public:

	ObjMeshObject();
	virtual ~ObjMeshObject();

	// mesh create
	static ObjMeshPtr Create( const string& fileName );

public:

	// load mesh model
	virtual void LoadModel( const string& fileName );

	// load texture file
	virtual void LoadTexture( const string& fileName );

	// mesh render
	virtual void Render();

private:

	// create mesh
	HRESULT Init( const ObjMesh& objMesh, bool flipTriangles, bool flipUVs );

	// this optimization requires sorting and/or searching which can be quite slow for heavy meshes.
	HRESULT InitVB( const ObjMesh& objMesh, bool flipTriangles, bool flipUVs );

private:

	UINT _triCount;
	UINT _vertexSize;
	DWORD _FVF;
	LPDIRECT3DVERTEXBUFFER9 _VB;

	// bounding box
	Float3 _bbmin;
	Float3 _bbmax;

	// texture
	LPDIRECT3DTEXTURE9 _texture;
};
