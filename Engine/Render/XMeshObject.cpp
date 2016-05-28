#include "RenderPCH.h"
#include "CreateD3D9.h"
#include "XMeshObject.h"



XMeshObject::XMeshObject() : 
	_objectName("Unknown"), 
	_texture(nullptr), 
	_materials(nullptr), 
	_numMaterials(0L), 
	_mtrlBuffer(nullptr)
{
	_shader = Shader::Create();

	_matrix = new Matrix();
}

XMeshObject::XMeshObject(const string& object_name)
{
	XMeshObject();

	SetObjectName(object_name);
}

XMeshObject::~XMeshObject()
{
	Clear();
}

XMeshObject* XMeshObject::Create(const string& fileName)
{
	XMeshObject* mesh = new XMeshObject();

	if (!mesh->LoadModel(fileName))
	{
		SAFE_DELETE(mesh);
	}

	return mesh;
}

void XMeshObject::SetObjectName(const string& objectName)
{
	_objectName = objectName;
}

bool XMeshObject::LoadModel(const string& fileName)
{
	auto meshLoad = FAILED(D3DXLoadMeshFromX(fileName.c_str(), D3DXMESH_SYSTEMMEM, D3D9_DEVICE, NULL, &_mtrlBuffer, NULL, &_numMaterials, &_mesh));

	// if fail to load mesh data
	if (meshLoad)
	{
		// assert
		assert(!meshLoad);

		return false;
	}

	// save materials data
	_d3dxMaterials = (D3DXMATERIAL*)_mtrlBuffer->GetBufferPointer();

	// default texture
	if (!LoadTexture(DEFAULT_TEX))
	{
		return false;
	}

	return true;
}

bool XMeshObject::LoadTexture(const string& fileName)
{
	// if texture does not exist
	if (fileName.c_str() == nullptr || lstrlenA(fileName.c_str()) < 0)
	{
		return false;
	}

	if ((_materials = new D3DMATERIAL9[_numMaterials]) == nullptr)
	{
		return false;
	}

	if ((_texture = new LPDIRECT3DTEXTURE9[_numMaterials]) == nullptr)
	{
		return false;
	}
	 
	for (auto i = 0; i < _numMaterials; i++)
	{
		_materials[i]				= _d3dxMaterials[i].MatD3D;		// 재질 정보 복사
		_materials[i].Ambient		= _materials[i].Diffuse;		// 재질용 주변광 색깔 설정

		_texture[i] = nullptr;

		auto textureLoad = D3DXCreateTextureFromFileA(D3D9_DEVICE, fileName.c_str(), &_texture[i]);

		// if fail to load texture
		if (textureLoad)
		{
			// assert
			assert(!FAILED(textureLoad));

			return false;
		}
	}

	return true;
}

void XMeshObject::Clear()
{
	if (_mtrlBuffer)
	{
		SAFE_RELEASE(_mtrlBuffer);
	}

	if (_materials)
	{
		SAFE_DELETE(_materials);
	}

	if (_shader)
	{
		_shader->Clear();
		SAFE_DELETE(_shader);
	}

	if (_texture)
	{
		SAFE_DELETE(_texture);
	}

	if (_mesh)
	{
		SAFE_RELEASE(_mesh);
	}

	if (_matrix)
	{
		SAFE_DELETE(_matrix);
	}
}