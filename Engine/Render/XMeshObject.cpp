#include "RenderPCH.h"
#include "CreateD3D9.h"
#include "XMeshObject.h"



XMeshObject::XMeshObject() : _objectName("Unknown"), _texture(nullptr), _materials(nullptr), _numMaterials(0L), _mtrlBuffer(nullptr)
{
	_shader = new Shader();

	_matrix = new Matrix();
}

XMeshObject::XMeshObject(string object_name)
{
	XMeshObject();

	SetObjectName(object_name);
}

XMeshObject::~XMeshObject()
{
	Clear();
}

void XMeshObject::SetObjectName(string objectName)
{
	_objectName = objectName;
}

MeshData* XMeshObject::GetMeshData()
{
	MeshData* object			= new MeshData();

	object->_mesh				= _mesh;
	object->_texture			= _texture;
	object->_d3dxMaterials		= _d3dxMaterials;
	object->_materials			= _materials;
	object->_numMaterials		= _numMaterials;

	return object;
}

void XMeshObject::LoadModel(const string& fileName)
{
	if (FAILED(D3DXLoadMeshFromX(fileName.c_str(), D3DXMESH_SYSTEMMEM, D3D9_DEVICE, NULL, &_mtrlBuffer, NULL, &_numMaterials, &_mesh)))
	{
		MessageBox(nullptr, "Could not find *.x file", "ninetail rendering engine", MB_OK);

		return;
	}

	_d3dxMaterials = (D3DXMATERIAL*)_mtrlBuffer->GetBufferPointer();

	// mesh를 생성하면 기본 텍스쳐를 입혀줌
	LoadTexture(DEFAULT_TEX);
}

void XMeshObject::LoadTexture(const string& fileName)
{
	// if texture does not exist
	if (fileName.c_str() == nullptr || lstrlenA(fileName.c_str()) < 0)
	{
		return;
	}

	if ((_materials = new D3DMATERIAL9[_numMaterials]) == nullptr)
	{
		return;
	}

	if ((_texture = new LPDIRECT3DTEXTURE9[_numMaterials]) == nullptr)
	{
		return;
	}
	 
	for (auto i = 0; i < _numMaterials; i++)
	{
		_materials[i]				= _d3dxMaterials[i].MatD3D;		// 재질 정보 복사
		_materials[i].Ambient		= _materials[i].Diffuse;		// 재질용 주변광 색깔 설정

		_texture[i] = nullptr;

		if (FAILED(D3DXCreateTextureFromFileA(D3D9_DEVICE, fileName.c_str(), &_texture[i])))
		{
			MessageBox(nullptr, "failed texture file loading", "ninetail rendering engine", MB_OK);

			return;
		}
	}
}

void XMeshObject::Clear()
{
	if (_mtrlBuffer)
		_mtrlBuffer->Release();

	if (_matrix)
		SAFE_DELETE(_matrix);
}