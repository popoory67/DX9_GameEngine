#pragma once

//#include "RenderPCH.h"
#include "Shader.h"


typedef struct _objectData
{
	// mesh data
	LPD3DXMESH					_mesh;

	// texture data
	LPDIRECT3DTEXTURE9*			_texture;

	// material datas
	D3DXMATERIAL*				_d3dxMaterials;
	D3DMATERIAL9*				_materials;
	DWORD						_numMaterials;

	_objectData::_objectData() : _texture(NULL), _materials(NULL), _numMaterials(0L)
	{
	
	}

} ObjectData;


class MeshObject
{
public:
	MeshObject();
	MeshObject(string object_name);
	~MeshObject();

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
	ObjectData*					GetObjectData();

	SHARED_PTR(Shader)			GetShader();

public:

	void						LoadModel(string file_name);
	//void						LoadModel(string model_file, string texture_name);
	void						LoadTexture(string file_name);

	D3DXMATRIX					Transform();

	D3DXMATRIX					Scale(float xpos = 1, float ypos = 1, float zpos = 1);
	D3DXMATRIX					Rotate(float xpos = 0, float ypos = 0, float zpos = 0);
	D3DXMATRIX					Position(float xpos = 0, float ypos = 0, float zpos = 0);

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
	SHARED_PTR(Shader)			_shader;

private:

	D3DXMATRIX					_scale;
	D3DXMATRIX					_rotation;
	D3DXMATRIX					_position;
};

