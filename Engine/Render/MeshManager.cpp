#include "RenderPCH.h"
#include "MeshManager.h"

#include "CreateD3D9.h"
//#include "CreateD3D11.h"
#include "CameraManager.h"


MeshManager* MeshManager::_instance = nullptr;

MeshManager::MeshManager()
{
	CameraManager::Get().AddCamera();
}

MeshManager::~MeshManager()
{
	if (_instance)
	{
		SAFE_DELETE(_instance);
	}
}

MeshManager& MeshManager::Get()
{
	if (!_instance)
	{
		_instance = new MeshManager();
	}

	return *_instance;
}

void MeshManager::AddMesh(XMeshObjectPtr mesh)
{
	_xVector.push_back(mesh);
}

void MeshManager::AddMesh(ObjMeshObjectPtr mesh)
{
	_objVector.push_back(mesh);
}

ObjMeshObjectPtr MeshManager::GetMesh(const int& id) const
{
	return _objVector[id];
}

void MeshManager::Init()
{

}


void MeshManager::Render()
{
	if (_xVector.size() > 0)
	{
		XFileRender();
	}

	if (_objVector.size() > 0)
	{
		ObjFileRender();
	}
}

void MeshManager::Clear()
{
	_xVector.clear();
	_objVector.clear();
}

void MeshManager::XFileRender()
{
	auto cameraMatrix	= CameraManager::Get().GetCamera(0)->GetCameraMatrix(); // camera matrix

	auto xFileIter		= _xVector.begin(); // mesh iterator

	while (xFileIter != _xVector.end())
	{
		auto meshData		= (*xFileIter)->GetMeshData();

		auto mesh			= meshData._mesh; // mesh data
		auto texture		= meshData._texture; // texture
		auto numMaterials	= meshData._numMaterials; // the number of materials
		auto materials		= meshData._materials; // meterial data
		auto matrix			= (*xFileIter)->GetMatrix(); // mesh matrix object
		auto effect			= (*xFileIter)->GetShader()->GetEffect(); // effect
		//auto shader = (*xFileIter)->GetShader();

		UINT pass = 0;

		// if exist mesh and succeed shader start
		if (mesh)
		{
			// because initialize default shader, The begin function always succeeded
			if (SUCCEEDED(effect->Begin(&pass, 0)))
			{
				// start shader render
				effect->BeginPass(0);

				auto shaderFunc = bind(
					[&]()
					{
						if (texture)
						{
							effect->SetTexture("texDiffuse", *texture);
							effect->SetBool("useDiffuseTexture", true);
						}

						D3DXMATRIX mWVP, mWI, mWIT;
						mWVP = cameraMatrix->_world * matrix->Transform() * cameraMatrix->_view * cameraMatrix->_proj;
						D3DXMatrixInverse(&mWI, NULL, &cameraMatrix->_world);
						D3DXMatrixTranspose(&mWIT, &mWI);

						effect->SetMatrix("mWorld", &cameraMatrix->_world);
						effect->SetMatrix("mWVP", &mWVP);
						effect->SetMatrix("mWIT", &mWIT);

						effect->SetFloatArray("vEye", &cameraMatrix->_eyePt.x, 3);
						effect->CommitChanges();
					}
				);

				shaderFunc();

				// end shader render
				effect->EndPass();
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
			effect->End();
		}

		// next mesh
		xFileIter++;
	}
}

void MeshManager::ObjFileRender()
{
	auto cameraMatrix	= CameraManager::Get().GetCamera(0)->GetCameraMatrix(); // camera matrix

	auto objFileIter	= _objVector.begin(); // mesh iterator

	while (objFileIter != _objVector.end())
	{
		auto meshData	= (*objFileIter)->GetMeshData(); // mesh data
		auto texture	= (*objFileIter)->GetTexture(); // texture
		auto matrix		= (*objFileIter)->GetMatrix(); // mesh matrix object
		auto effect		= (*objFileIter)->GetShader()->GetEffect(); // effect

		UINT pass = 0;

		if (SUCCEEDED(effect->Begin(&pass, 0)))
		{
			effect->BeginPass(0);

			if (texture)
			{
				effect->SetTexture("texDiffuse", texture);
				effect->SetBool("useDiffuseTexture", true);
			}

			D3DXMATRIX mWVP, mWI, mWIT;
			mWVP = cameraMatrix->_world * matrix->Transform() * cameraMatrix->_view * cameraMatrix->_proj;
			D3DXMatrixInverse(&mWI, NULL, &cameraMatrix->_world);
			D3DXMatrixTranspose(&mWIT, &mWI);

			effect->SetMatrix("mWorld", &cameraMatrix->_world);
			effect->SetMatrix("mWVP", &mWVP);
			effect->SetMatrix("mWIT", &mWIT);

			effect->SetFloatArray("vEye", &cameraMatrix->_eyePt.x, 3);
			effect->CommitChanges();

			effect->EndPass();
		}

		// mesh render
		//D3D9_DEVICE->SetTransform(D3DTS_WORLD, &matrix->Transform());
		D3D9_DEVICE->SetStreamSource(0, meshData->_VB, 0, meshData->_vertexSize);
		D3D9_DEVICE->SetFVF(meshData->_FVF);
		D3D9_DEVICE->DrawPrimitive(D3DPT_TRIANGLELIST, 0, meshData->_triCount);

		// end shader
		effect->End();

		// next mesh
		objFileIter++;
	}
}