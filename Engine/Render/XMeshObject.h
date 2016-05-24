#pragma once

#include "Matrix.h"
#include "Shader.h"

#define DEFAULT_TEX			"C:/Users/boseul/Documents/GitHub/NinetailEngine/Engine/Resource/texture.png"

struct MeshData
{ 
	// mesh data
	LPD3DXMESH					_mesh;

	// texture data
	LPDIRECT3DTEXTURE9*			_texture;

	// material datas
	D3DXMATERIAL*				_d3dxMaterials;
	D3DMATERIAL9*				_materials;
	DWORD						_numMaterials;

	MeshData::MeshData() : _texture(NULL), _materials(NULL), _numMaterials(0L)
	{
	
	}

};


class XMeshObject
{
public:
	XMeshObject();
	XMeshObject(string object_name);
	~XMeshObject();

	/**
	 * set this object's name
	 * if you don't want to set object name, set the name "Unknown"
	 */
	void SetObjectName(string objectName);

	/**
	 * get modeling data
	 * @return mesh, texture and meterials data
	 */
	MeshData* GetMeshData();

	Shader* GetShader() { return _shader; }

	Matrix* GetMatrix() { return _matrix; }

	void LoadModel(const string& fileName);

	void LoadTexture(const string& fileName);

private:

	void Clear();

private:

	string _objectName;

	// mesh data
	LPD3DXMESH _mesh;

	// texture data
	LPDIRECT3DTEXTURE9* _texture;

	// material datas
	LPD3DXBUFFER _mtrlBuffer;
	D3DXMATERIAL* _d3dxMaterials;
	D3DMATERIAL9* _materials;
	DWORD _numMaterials;

	// shader object
	Shader* _shader;

	// mesh transform object
	Matrix* _matrix;
};

