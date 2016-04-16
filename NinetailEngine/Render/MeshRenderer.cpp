#include "RenderPCH.h"
#include "MeshRenderer.h"

MeshRenderer::MeshRenderer()
{
	_object = new ::vector< ::tr1::shared_ptr<MeshObject> >();
}

MeshRenderer::~MeshRenderer()
{

}

// 함수명 바꿔야함
void MeshRenderer::Init()
{
	::tr1::shared_ptr<MeshObject> object(new MeshObject());

	object->LoadModel(BODY);
	object->Scale(0.05, 0.05, 0.05);

	_object->push_back(object);

	::tr1::shared_ptr<MeshObject> tiger(new MeshObject());

	tiger->LoadModel(TIGER);
	tiger->Scale(10, 10, 10);
	tiger->Position(10, 10, 10);

	_object->push_back(tiger);
}


void MeshRenderer::Render()
{
	Init();

	auto iter = _object->begin();

	while (iter != _object->end())
	{
		auto mesh			= (*iter)->GetObjectData()->_mesh;
		auto texture		= (*iter)->GetObjectData()->_texture;
		auto numMaterials	= (*iter)->GetObjectData()->_numMaterials;
		auto materials		= (*iter)->GetObjectData()->_materials;
		
		auto transform		= (*iter)->Transform();

		if (mesh)
		{
			for (DWORD i = 0; i < numMaterials; i++)
			{
				D3DX_DEVICE->SetTransform(D3DTS_WORLD, &transform);
				D3DX_DEVICE->SetMaterial(&materials[i]);

				if (texture)
				{
					D3DX_DEVICE->SetTexture(0, texture[i]);
				}

				mesh->DrawSubset(i);
			}
		}

		iter++;
	}
}


void MeshRenderer::Release()
{
	_object->clear();
}