#pragma once

#include "MeshModel.h"

class XMeshObject;

using XMeshPtr = shared_ptr<XMeshObject>;

class XMeshObject : public MeshModel
{
public:

	XMeshObject();
	XMeshObject( const string& object_name );
	virtual ~XMeshObject();

	// resource acquisition is initialization.
	static XMeshPtr Create( const string& fileName );

public:

	// load .x file modeling
	void LoadModel( const string& fileName );

	// load texture
	bool LoadTexture( const string& fileName );

	// Render
	virtual void Render();

private:

	// mesh data
	LPD3DXMESH _mesh;

	// texture data
	LPDIRECT3DTEXTURE9* _texture;

	// material datas
	LPD3DXBUFFER _mtrlBuffer;
	D3DXMATERIAL* _d3dxMaterials;
	D3DMATERIAL9* _materials;
	DWORD _numMaterials;
};

