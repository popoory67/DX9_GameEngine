#include "RenderPCH.h"
#include "Renderer.h"

#include "CreateD3D9.h"
//#include "CreateD3D11.h"

Renderer* Renderer::_instance = NULL;

Renderer::Renderer()
{
	_xMesh = new XMeshVector();

	_objMesh = new ObjMeshVector();
}

Renderer::~Renderer()
{
	if (_instance)
	{
		SAFE_DELETE (_instance);
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

void Renderer::AddMesh(XMeshObjectPtr mesh)
{
	_xMesh->push_back(mesh);
}

void Renderer::AddMesh(ObjMeshObjectPtr mesh)
{
	_objMesh->push_back(mesh);
}


void Renderer::Init()
{

}


void Renderer::Render()
{
	auto xFileIter = _xMesh->begin();
	auto objFileIter = _objMesh->begin();

	while (xFileIter != _xMesh->end())
	{
		auto objectData		= (*xFileIter)->GetObjectData();

		auto mesh			= objectData->_mesh;
		auto texture		= objectData->_texture;
		auto numMaterials	= objectData->_numMaterials;
		auto materials		= objectData->_materials;
		
		auto transform		= (*xFileIter)->GetMatrix()->Transform();

		if (mesh)
		{
			for (DWORD i = 0; i < numMaterials; i++)
			{

				D3D9_DEVICE->SetTransform(D3DTS_WORLD, &transform);

				if (materials)
				{
					D3D9_DEVICE->SetMaterial(&materials[i]);
				}

				if (texture)
				{
					D3D9_DEVICE->SetTexture(0, texture[i]);
				}

				mesh->DrawSubset(i);

			}
		}

		xFileIter++;
	}

	while (objFileIter != _objMesh->end())
	{
		D3D9_DEVICE->SetStreamSource(0, (*objFileIter)->GetMesh()->_VB, 0, (*objFileIter)->GetMesh()->_vertexSize);

		D3D9_DEVICE->SetFVF((*objFileIter)->GetMesh()->_FVF);

		D3D9_DEVICE->DrawPrimitive(D3DPT_TRIANGLELIST, 0, (*objFileIter)->GetMesh()->_triCount);

		objFileIter++;
	}
}


void Renderer::Clear()
{
	_xMesh->clear();
	_objMesh->clear();
}