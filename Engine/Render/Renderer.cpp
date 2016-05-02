#include "RenderPCH.h"
#include "Renderer.h"

#include "CreateDeviceD3DX.h"
//#include "CreateD3D11.h"


Renderer* Renderer::_instance = NULL;

Renderer::Renderer()
{
	_object = new MeshVector();
}

Renderer::~Renderer()
{
	if (_instance)
	{
		delete (_instance);
	}
}

Renderer& Renderer::Get()
{
	if (!_instance)
	{
		_instance = new Renderer();
	}

	return *_instance;
}

void Renderer::AddMesh(MeshObjectPointer mesh)
{
	_object->push_back(mesh);
}


void Renderer::Init()
{

}

void Renderer::Render()
{
	auto iter			= _object->begin();
	//UINT numPasses		= 0;

	while (iter != _object->end())
	{
		auto objectData		= (*iter)->GetObjectData();

		auto mesh			= objectData->_mesh;
		auto texture		= objectData->_texture;
		auto numMaterials	= objectData->_numMaterials;
		auto materials		= objectData->_materials;
		
		auto transform		= (*iter)->GetMatrix()->Transform();

		//auto shader			= (*iter)->GetShader()->LoadShader(PHONG_BUMP_REFLECT);

		//shader->Begin(&numPasses, NULL);

		if (mesh)
		{
			for (DWORD i = 0; i < numMaterials; i++)
			{
				//shader->BeginPass(i);

				D3DX_DEVICE->SetTransform(D3DTS_WORLD, &transform);

				if (materials)
				{
					D3DX_DEVICE->SetMaterial(&materials[i]);
				}

				if (texture)
				{
					D3DX_DEVICE->SetTexture(0, texture[i]);
				}

				mesh->DrawSubset(i);

				//shader->EndPass();
			}
		}

		iter++;
	}
}


void Renderer::Release()
{
	_object->clear();
}