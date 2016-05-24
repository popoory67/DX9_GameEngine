#pragma once

#include "ObjLoader.h"
#include "Matrix.h"
#include "Shader.h"

// test
#define DEFAULT_TEX			"C:/Users/boseul/Documents/GitHub/NinetailEngine/Engine/Resource/texture.png"

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

	static ObjMeshObject* Create(LPCTSTR fileName);

	MeshData* GetMeshData() { return _mesh; }

	LPDIRECT3DTEXTURE9 GetTexture() { return _texture; }

	Shader* GetShader() { return _shader; }

	Matrix* GetMatrix() { return _matrix; }

	void LoadTexture(const string& fileName);

private:

	HRESULT Init(const ObjMesh& objMesh, bool flipTriangles, bool flipUVs);

	// This optimization requires sorting and/or searching which can be quite slow for heavy meshes.
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
