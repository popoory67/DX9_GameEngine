#pragma once

#include "ObjLoader.h"
#include "Matrix.h"
#include "Shader.h"

class ObjMeshObject
{

private:

	struct MeshData
	{
		UINT _triCount;

		UINT _vertexSize;

		DWORD _FVF;

		LPDIRECT3DVERTEXBUFFER9 _VB;

		MeshData() : _vertexSize(0), _FVF(0), _VB(NULL)
		{

		}
	};

public:

	ObjMeshObject();
	~ObjMeshObject();

	static ObjMeshObject* Create(const string& fileName);

	MeshData* GetMeshData() const { return _mesh; }

	LPDIRECT3DTEXTURE9 GetTexture() const { return _texture; }

	Shader* GetShader() const { return _shader; }

	Matrix* GetMatrix() const { return _matrix; }

	void LoadTexture(const string& fileName);

private:

	// create mesh
	HRESULT Init(const ObjMesh& objMesh, bool flipTriangles, bool flipUVs);

	// this optimization requires sorting and/or searching which can be quite slow for heavy meshes.
	HRESULT InitVB(const ObjMesh& objMesh, bool flipTriangles, bool flipUVs);

	void Clear();

private:

	MeshData* _mesh;

	// bounding box
	D3DXVECTOR3 _bbmin;
	D3DXVECTOR3 _bbmax;

	// texture
	LPDIRECT3DTEXTURE9 _texture;

	// shader
	Shader* _shader;

	// object transform
	Matrix* _matrix;
};
