#pragma once

#include "ObjLoader.h"


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

	MeshData* GetMesh() { return _mesh; }

	static ObjMeshObject* Create(LPCTSTR fileName);

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
};
