#include "RenderPCH.h"
#include "CreateDeviceD3DX.h"
#include "MeshRenderer.h"

MeshRenderer::MeshRenderer()
{
	_object = new MeshVectorPtr();
}

MeshRenderer::~MeshRenderer()
{

}

// 함수명 바꿔야함
void MeshRenderer::Init()
{
 	SHARED_PTR(MeshObject) object(new MeshObject());

	//object->LoadModel(BODY, TEXTURE);
	object->LoadModel(BODY);
	object->LoadTexture(TEXTURE);
	object->Scale(0.05f, 0.05f, 0.05f);

	_object->push_back(object);

	SHARED_PTR(MeshObject) tiger(new MeshObject());

	tiger->LoadModel(TIGER);
	tiger->LoadTexture(TEXTURE2);
	tiger->Scale(10, 10, 10);
	tiger->Position(10, 10, 10);

	_object->push_back(tiger);
}


void MeshRenderer::Render()
{
	Init();

	auto iter			= _object->begin();
	//UINT numPasses		= 0;

	while (iter != _object->end())
	{
		auto mesh			= (*iter)->GetObjectData()->_mesh;
		auto texture		= (*iter)->GetObjectData()->_texture;
		auto numMaterials	= (*iter)->GetObjectData()->_numMaterials;
		auto materials		= (*iter)->GetObjectData()->_materials;
		
		auto transform		= (*iter)->Transform();

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


void MeshRenderer::Release()
{
	_object->clear();
}