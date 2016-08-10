#pragma once

#include "ObjLoader.h"
#include "MeshModel.h"

class ObjMeshObject;

using ObjMeshPtr = shared_ptr<ObjMeshObject>;

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
	HRESULT Init(const ObjMesh& objMesh, bool flipTriangles, bool flipUVs);

	// this optimization requires sorting and/or searching which can be quite slow for heavy meshes.
	HRESULT InitVB(const ObjMesh& objMesh, bool flipTriangles, bool flipUVs);

private:

	UINT _triCount;
	UINT _vertexSize;
	DWORD _FVF;
	LPDIRECT3DVERTEXBUFFER9 _VB;

	// bounding box
	D3DXVECTOR3 _bbmin;
	D3DXVECTOR3 _bbmax;

	// texture
	LPDIRECT3DTEXTURE9 _texture;
};
