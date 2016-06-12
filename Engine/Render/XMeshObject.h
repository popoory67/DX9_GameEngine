#pragma once

#include "Matrix.h"
#include "Shader.h"

#define DEFAULT_TEX "C:/Users/boseul/Documents/GitHub/NinetailEngine/Engine/Resource/texture.png"


class XMeshObject
{
private:

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

		MeshData::~MeshData()
		{
			if (_texture)
			{
				SAFE_DELETE(_texture);
			}

			if (_materials)
			{
				SAFE_DELETE(_materials);
			}

			if (_mesh)
			{
				SAFE_RELEASE(_mesh);
			}
		}
	};

public:
	XMeshObject();
	XMeshObject(const string& object_name);
	~XMeshObject();

	// resource acquisition is initialization.
	static XMeshObject* Create(const string& fileName);

	/**
	 * set this object's name.
	 * if you don't want to set object name, set the dafault name "Unknown".
	 */
	void SetObjectName(const string& objectName);

	/**
	 * get modeling data.
	 * @returns mesh, texture and meterials data.
	 */
	MeshData GetMeshData() const
	{
		MeshData object;

		object._mesh = _mesh;
		object._texture = _texture;
		object._d3dxMaterials = _d3dxMaterials;
		object._materials = _materials;
		object._numMaterials = _numMaterials;

		return object;
	}

	// get shader instance
	Shader* GetShader() const { return _shader; }

	// get matrix instance
	Matrix* GetMatrix() const { return _matrix; }

public:

	// load .x file modeling
	bool LoadModel(const string& fileName);

	// load texture
	bool LoadTexture(const string& fileName);

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

