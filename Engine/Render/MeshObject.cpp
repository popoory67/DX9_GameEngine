#include "RenderPCH.h"
#include "CreateDeviceD3DX.h"
#include "MeshObject.h"


MeshObject::MeshObject() : _objectName("Unknown"), _texture(NULL), _materials(NULL), _numMaterials(0L), _mtrlBuffer(NULL)
{
	_matrix = new Matrix();
}

MeshObject::MeshObject(string object_name)
{
	MeshObject();
	SetObjectName(object_name);
}

MeshObject::~MeshObject()
{
	if (_mtrlBuffer)
		_mtrlBuffer->Release();
}

void MeshObject::SetObjectName(string object_name)
{
	_objectName = object_name;
}

MeshData* MeshObject::GetObjectData()
{
	MeshData* object			= new MeshData();

	object->_mesh				= _mesh;
	object->_texture			= _texture;
	object->_d3dxMaterials		= _d3dxMaterials;
	object->_materials			= _materials;
	object->_numMaterials		= _numMaterials;

	return object;
}

SHARED_PTR(Shader) MeshObject::GetShader()
{
	return _shader;
}

Matrix* MeshObject::GetMatrix()
{
	return _matrix;
}

//void MeshObject::LoadModel(string model_file, string texture_name)
//{
//	LoadModel(model_file);
//	LoadTexture(texture_name);
//}

void MeshObject::LoadModel(string file_name)
{
	if ( FAILED ( D3DXLoadMeshFromX(file_name.c_str(), D3DXMESH_SYSTEMMEM, D3DX_DEVICE, NULL, &_mtrlBuffer, NULL, &_numMaterials, &_mesh ) ) )
	{
		MessageBox(NULL, "Could not find *.x file", "ninetail rendering engine", MB_OK);

		return;
	}

	_d3dxMaterials = (D3DXMATERIAL*)_mtrlBuffer->GetBufferPointer();
}

void MeshObject::LoadTexture(string file_name)
{
	// if texture does not exist
	if (file_name.c_str() == NULL || lstrlenA(file_name.c_str()) < 0)
	{
		return;
	}

	if ((_materials = new D3DMATERIAL9[_numMaterials]) == NULL)
	{
		return;
	}

	if ((_texture = new LPDIRECT3DTEXTURE9[_numMaterials]) == NULL)
	{
		return;
	}
	 
	for (auto i = 0; i < _numMaterials; i++)
	{
		_materials[i]				= _d3dxMaterials[i].MatD3D;		// 재질 정보 복사
		_materials[i].Ambient		= _materials[i].Diffuse;		// 재질용 주변광 색깔 설정

		_texture[i] = NULL;

		if ( FAILED ( D3DXCreateTextureFromFileA(D3DX_DEVICE, file_name.c_str(), &_texture[i] ) ) )
		{
			MessageBox(NULL, "failed texture file loading", "ninetail rendering engine", MB_OK);
		}
	}
}

//
//D3DXMATRIX MeshObject::Transform()
//{
//	D3DXMATRIX worldMatrix;
//
//	worldMatrix = _scale * _rotation * _position;
//
//	return worldMatrix;
//}
//
//
//D3DXMATRIX MeshObject::Scale(float xpos, float ypos, float zpos)
//{
//	D3DXMatrixScaling(&_scale, xpos, ypos, zpos);
//
//	return _scale;
//}
//
//D3DXMATRIX MeshObject::Rotate(float xpos, float ypos, float zpos)
//{
//	// rotation function
//
//	return _rotation;
//}
//
//D3DXMATRIX MeshObject::Position(float xpos, float ypos, float zpos)
//{
//	D3DXMatrixTranslation(&_position, xpos, ypos, zpos);
//
//	return _position;
//}