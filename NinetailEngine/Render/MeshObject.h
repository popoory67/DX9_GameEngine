#pragma once

#include "CreateDeviceD3DX.h"

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

	void						SetObjectName(string object_name);

	/**
	 * get modeling data
	 * @return mesh, texture and meterials data
	 */
	ObjectData*					GetObjectData();

	void						LoadModel(string file_name);
	LPDIRECT3DTEXTURE9*			LoadTexture();

public:

	D3DXMATRIX					Transform();

	D3DXMATRIX					Scale(float xpos = 1, float ypos = 1, float zpos = 1);
	D3DXMATRIX					Rotate(float xpos = 0, float ypos = 0, float zpos = 0);
	D3DXMATRIX					Position(float xpos = 0, float ypos = 0, float zpos = 0);

private:

	D3DXMATRIX					_scale;
	D3DXMATRIX					_rotation;
	D3DXMATRIX					_position;

private:

	::string					_objectName;

	// mesh data
	LPD3DXMESH					_mesh;

	// texture data
	LPDIRECT3DTEXTURE9*			_texture;

	// material datas
	D3DXMATERIAL*				_d3dxMaterials;
	D3DMATERIAL9*				_materials;
	DWORD						_numMaterials;
};

