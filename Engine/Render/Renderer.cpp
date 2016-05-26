#include "RenderPCH.h"
#include "Renderer.h"

#include "CreateD3D9.h"
//#include "CreateD3D11.h"

Renderer* Renderer::_instance = NULL;

Renderer::Renderer()
{
	_mainCamera = Camera::Create();

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
	if (_xMesh->size() > 0)
	{
		XFileRender();
	}

	if (_objMesh->size() > 0)
	{
		ObjFileRender();
	}
}


void Renderer::Clear()
{
	SAFE_DELETE(_mainCamera);

	_xMesh->clear();
	_objMesh->clear();
}

void Renderer::XFileRender()
{
	auto cameraMatirx	= _mainCamera->GetCameraMatrix(); // camera matrix

	auto xFileIter		= _xMesh->begin(); // mesh iterator

	while (xFileIter != _xMesh->end())
	{
		auto meshData		= (*xFileIter)->GetMeshData();

		auto mesh			= meshData->_mesh; // mesh data
		auto texture		= meshData->_texture; // texture
		auto numMaterials	= meshData->_numMaterials; // the number of materials
		auto materials		= meshData->_materials; // meterial data
		auto matrix			= (*xFileIter)->GetMatrix(); // mesh matrix object
		auto shader			= (*xFileIter)->GetShader()->GetEffect(); // effect

		UINT pass = 0;

		// if exist mesh and succeed shader start
		if (mesh)
		{
			// because initialize default shader, The begin function always succeeded
			if (SUCCEEDED(shader->Begin(&pass, 0)))
			{
				// start shader render
				shader->BeginPass(0);

				if (texture)
				{
					shader->SetTexture("texDiffuse", *texture);
					shader->SetBool("useDiffuseTexture", true);
				}

				D3DXMATRIX mWVP, mWI, mWIT;
				mWVP = cameraMatirx->_world * matrix->Transform() * cameraMatirx->_view * cameraMatirx->_proj;
				D3DXMatrixInverse(&mWI, NULL, &cameraMatirx->_world);
				D3DXMatrixTranspose(&mWIT, &mWI);

				shader->SetMatrix("mWorld", &cameraMatirx->_world);
				shader->SetMatrix("mWVP", &mWVP);
				shader->SetMatrix("mWIT", &mWIT);

				shader->SetFloatArray("vEye", &cameraMatirx->_eyePt.x, 3);
				shader->CommitChanges();

				// end shader render
				shader->EndPass();
			}

			for (DWORD i = 0; i < numMaterials; i++)
			{
				if (materials)
				{
					D3D9_DEVICE->SetMaterial(&materials[i]);
				}

				mesh->DrawSubset(i);
			}

			// end shader
			shader->End();
		}

		// next mesh
		xFileIter++;
	}
}

void Renderer::ObjFileRender()
{
	auto cameraMatirx	= _mainCamera->GetCameraMatrix(); // camera matrix

	auto objFileIter	= _objMesh->begin(); // mesh iterator

	while (objFileIter != _objMesh->end())
	{
		auto meshData	= (*objFileIter)->GetMeshData(); // mesh data
		auto texture	= (*objFileIter)->GetTexture(); // texture
		auto matrix		= (*objFileIter)->GetMatrix(); // mesh matrix object
		auto shader		= (*objFileIter)->GetShader()->GetEffect(); // effect

		UINT pass = 0;

		if (SUCCEEDED(shader->Begin(&pass, 0)))
		{
			shader->BeginPass(0);

			if (texture)
			{
				shader->SetTexture("texDiffuse", texture);
				shader->SetBool("useDiffuseTexture", true);
			}

			D3DXMATRIX mWVP, mWI, mWIT;
			mWVP = cameraMatirx->_world * matrix->Transform() * cameraMatirx->_view * cameraMatirx->_proj;
			D3DXMatrixInverse(&mWI, NULL, &cameraMatirx->_world);
			D3DXMatrixTranspose(&mWIT, &mWI);

			shader->SetMatrix("mWorld", &cameraMatirx->_world);
			shader->SetMatrix("mWVP", &mWVP);
			shader->SetMatrix("mWIT", &mWIT);

			shader->SetFloatArray("vEye", &cameraMatirx->_eyePt.x, 3);
			shader->CommitChanges();

			shader->EndPass();
		}

		// mesh render
		//D3D9_DEVICE->SetTransform(D3DTS_WORLD, &matrix->Transform());
		D3D9_DEVICE->SetStreamSource(0, meshData->_VB, 0, meshData->_vertexSize);
		D3D9_DEVICE->SetFVF(meshData->_FVF);
		D3D9_DEVICE->DrawPrimitive(D3DPT_TRIANGLELIST, 0, meshData->_triCount);

		// end shader
		shader->End();

		// next mesh
		objFileIter++;
	}
}