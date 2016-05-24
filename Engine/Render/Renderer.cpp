#include "RenderPCH.h"
#include "Renderer.h"

#include "CreateD3D9.h"
//#include "CreateD3D11.h"

Renderer* Renderer::_instance = NULL;

Renderer::Renderer()
{
	_camera = Camera::Create();

	_shader = new Shader();

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
	//_shader->Init();
	//_shader->LoadShader("C:/Users/boseul/Documents/GitHub/NinetailEngine/Engine/Resource/ObjViewer.fx");

	auto xFileIter = _xMesh->begin();
	auto objFileIter = _objMesh->begin();

	auto cameraMatirx = _camera->GetCameraMatrix(); // camera matrix

	// .x file render
	while (xFileIter != _xMesh->end())
	{
		auto meshData = (*xFileIter)->GetMeshData();

		auto mesh = meshData->_mesh; // mesh data

		auto texture = meshData->_texture; // texture

		auto numMaterials = meshData->_numMaterials; // the number of materials

		auto materials = meshData->_materials; // meterial data
		
		auto matrix = (*xFileIter)->GetMatrix(); // mesh matrix object

		//auto shader = (*xFileIter)->GetShader()->GetEffect(); // shader

		UINT pass = 0;

		//_shader->GetEffect()->SetTexture("texDiffuse", *texture);
		//_shader->GetEffect()->SetBool("useDiffuseTexture", true);

		//D3DXMATRIX mWVP, mWI, mWIT;
		//mWVP = cameraMatirx->_world * cameraMatirx->_view * cameraMatirx->_proj;
		//D3DXMatrixInverse(&mWI, NULL, &cameraMatirx->_world);
		//D3DXMatrixTranspose(&mWIT, &mWI);

		//_shader->GetEffect()->GetMatrix("mWorld", &cameraMatirx->_world);
		//_shader->GetEffect()->GetMatrix("mWVP", &mWVP);
		//_shader->GetEffect()->GetMatrix("mWIT", &mWIT);

		//_shader->GetEffect()->SetFloatArray("vEye", &cameraMatirx->_eyePt.x, 3);
		//_shader->GetEffect()->CommitChanges();

		// if exist mesh and succeed shader start
		if (mesh && SUCCEEDED(_shader->GetEffect()->Begin(&pass, 0)))
		{
			// start shader
			//_shader->GetEffect()->BeginPass(0);

			for (DWORD i = 0; i < numMaterials; i++)
			{
				// transform
				D3D9_DEVICE->SetTransform(D3DTS_WORLD, &matrix->Transform());

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

			// end shader
			_shader->GetEffect()->EndPass();
			_shader->GetEffect()->End();
		}


		// next mesh
		xFileIter++;
	}

	// .obj file render
	while (objFileIter != _objMesh->end())
	{
		//auto meshData = (*objFileIter)->GetMeshData(); // mesh data

		//auto texture = (*objFileIter)->GetTexture(); // texture

		//auto matrix = (*objFileIter)->GetMatrix(); // mesh matrix object

		//auto shader = (*objFileIter)->GetShader()->GetEffect(); // shader

		UINT pass = 0;

		if (SUCCEEDED(_shader->GetEffect()->Begin(&pass, 0)))
		{
			// start shader
			//_shader->GetEffect()->BeginPass(0);

			auto meshData = (*objFileIter)->GetMeshData(); // mesh data

			auto texture = (*objFileIter)->GetTexture(); // texture

			auto matrix = (*objFileIter)->GetMatrix(); // mesh matrix object

			/*_shader->GetEffect()->SetTexture("texDiffuse", texture);
			_shader->GetEffect()->SetBool("useDiffuseTexture", true);

			D3DXMATRIX mWVP, mWI, mWIT;
			mWVP = cameraMatirx->_world * cameraMatirx->_view * cameraMatirx->_proj;
			D3DXMatrixInverse(&mWI, NULL, &cameraMatirx->_world);
			D3DXMatrixTranspose(&mWIT, &mWI);

			_shader->GetEffect()->GetMatrix("mWorld", &cameraMatirx->_world);
			_shader->GetEffect()->GetMatrix("mWVP", &mWVP);
			_shader->GetEffect()->GetMatrix("mWIT", &mWIT);

			_shader->GetEffect()->SetFloatArray("vEye", &cameraMatirx->_eyePt.x, 3);
			_shader->GetEffect()->CommitChanges();*/

			// mesh render
			D3D9_DEVICE->SetTransform(D3DTS_WORLD, &matrix->Transform());

			D3D9_DEVICE->SetStreamSource(0, meshData->_VB, 0, meshData->_vertexSize);

			D3D9_DEVICE->SetFVF(meshData->_FVF);

			D3D9_DEVICE->DrawPrimitive(D3DPT_TRIANGLELIST, 0, meshData->_triCount);

			// end shader
			_shader->GetEffect()->EndPass();
			_shader->GetEffect()->End();
		}

		// next mesh
		objFileIter++;
	}
}


void Renderer::Clear()
{
	SAFE_DELETE(_camera);
	SAFE_DELETE(_shader);

	_xMesh->clear();
	_objMesh->clear();
}