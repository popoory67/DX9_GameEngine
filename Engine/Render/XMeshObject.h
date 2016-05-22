#pragma once

#include "Matrix.h"
#include "Shader.h"


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
	void						SetObjectName(string object_name);

	/**
	 * get modeling data
	 * ObjectData is struct
	 * @return mesh, texture and meterials data
	 */
	MeshData*					GetObjectData();

	Shader*						GetShader();

	Matrix*						GetMatrix();

	void						LoadModel(const string& file_name);
	//void						LoadModel(string model_file, string texture_name);
	void						LoadTexture(const string& file_name);

	void						Clear();

private:

	::string					_objectName;

	// mesh data
	LPD3DXMESH					_mesh;

	// texture data
	LPDIRECT3DTEXTURE9*			_texture;

	// material datas
	LPD3DXBUFFER				_mtrlBuffer;
	D3DXMATERIAL*				_d3dxMaterials;
	D3DMATERIAL9*				_materials;
	DWORD						_numMaterials;

	// shader
	Shader*						_shader;

	// object transform
	Matrix*						_matrix;
};

