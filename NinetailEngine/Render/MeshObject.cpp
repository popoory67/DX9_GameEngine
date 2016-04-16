#include "RenderPCH.h"
#include "MeshObject.h"


MeshObject::MeshObject() : _objectName("Unknown"), _texture(NULL), _materials(NULL), _numMaterials(0L)
{
	D3DXMatrixIdentity(&_scale);
	D3DXMatrixIdentity(&_rotation);
	D3DXMatrixIdentity(&_position);
}

MeshObject::MeshObject(string object_name)
{
	MeshObject();
	SetObjectName(object_name);
}

MeshObject::~MeshObject()
{

}

void MeshObject::SetObjectName(string object_name)
{
	_objectName = object_name;
}

ObjectData* MeshObject::GetObjectData()
{
	ObjectData* object = new ObjectData();

	object->_mesh				= _mesh;
	object->_texture			= _texture;
	object->_d3dxMaterials		= _d3dxMaterials;
	object->_materials			= _materials;
	object->_numMaterials		= _numMaterials;

	return object;
}

void MeshObject::LoadModel(string file_name)
{
	LPD3DXBUFFER	pMtrlBuffer;

	if (FAILED(D3DXLoadMeshFromX(file_name.c_str(), D3DXMESH_SYSTEMMEM, D3DX_DEVICE,
		NULL, &pMtrlBuffer, NULL, &_numMaterials, &_mesh)))
	{
		MessageBox(NULL, "Could not find *.x file", "ninetail rendering engine", MB_OK);

		return;
	}

	_d3dxMaterials = (D3DXMATERIAL*)pMtrlBuffer->GetBufferPointer();

	if ((_texture = LoadTexture()) == NULL)
	{
		MessageBox(NULL, "failed texture file loading", "ninetail rendering engine", MB_OK);
	}

	pMtrlBuffer->Release();
}

LPDIRECT3DTEXTURE9* MeshObject::LoadTexture()
{
	LPDIRECT3DTEXTURE9*	ret;

	if ((_materials = new D3DMATERIAL9[_numMaterials]) == NULL)
	{
		return NULL;
	}

	if ((ret = new LPDIRECT3DTEXTURE9[_numMaterials]) == NULL)
	{
		return NULL;
	}

	// texture 경로 수정해야함 
	for (auto i = 0; i < _numMaterials; i++)
	{
		_materials[i]				= _d3dxMaterials[i].MatD3D;		// 재질 정보 복사
		_materials[i].Ambient		= _materials[i].Diffuse;		// 재질용 주변광 색깔 설정

		ret[i]						= NULL;

		if (_d3dxMaterials[i].pTextureFilename != NULL && lstrlenA(_d3dxMaterials[i].pTextureFilename) > 0)
		{
			D3DXCreateTextureFromFileA(D3DX_DEVICE, _d3dxMaterials[i].pTextureFilename, &ret[i]);
		}
	}

	return ret;
}


D3DXMATRIX MeshObject::Transform()
{
	D3DXMATRIX worldMatrix;

	worldMatrix = _scale * _rotation * _position;

	return worldMatrix;
}


D3DXMATRIX MeshObject::Scale(float xpos, float ypos, float zpos)
{
	D3DXMatrixScaling(&_scale, xpos, ypos, zpos);

	return _scale;
}

D3DXMATRIX MeshObject::Rotate(float xpos, float ypos, float zpos)
{
	// rotation function

	return _rotation;
}

D3DXMATRIX MeshObject::Position(float xpos, float ypos, float zpos)
{
	D3DXMatrixTranslation(&_position, xpos, ypos, zpos);

	return _position;
}