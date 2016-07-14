#include "RenderPCH.h"
#include "XMeshObject.h"

#include "CreateD3D9.h"
#include "CameraManager.h"


XMeshObject::XMeshObject() : _mtrlBuffer( nullptr )
{

}

XMeshObject::XMeshObject( const string& object_name )
{
	XMeshObject();

	SetObjectName( object_name );
}

XMeshObject::~XMeshObject()
{
	SAFE_RELEASE( _mtrlBuffer );

	SAFE_DELETE( _texture );

	SAFE_DELETE( _materials );

	SAFE_RELEASE( _mesh );
}

XMeshPtr XMeshObject::Create( const string& fileName )
{
	XMeshPtr mesh( new XMeshObject() );

	mesh->LoadModel( fileName );

	return mesh;
}


void XMeshObject::LoadModel( const string& fileName )
{
	auto meshLoad = FAILED( D3DXLoadMeshFromX(	fileName.c_str(), D3DXMESH_SYSTEMMEM, D3D9_DEVICE, NULL,
												&_mtrlBuffer, NULL, &_numMaterials, &_mesh ) );

	// if fail to load mesh data, assert
	assert( !meshLoad );

	// save materials data
	_d3dxMaterials = (D3DXMATERIAL*)_mtrlBuffer->GetBufferPointer();

	// default texture
	assert( LoadTexture( DEFAULT_TEX ) );
}

bool XMeshObject::LoadTexture( const string& fileName )
{
	// if texture does not exist
	if (fileName.c_str() == nullptr || lstrlenA( fileName.c_str() ) < 0)
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
		_materials[i] = _d3dxMaterials[i].MatD3D;		// 재질 정보 복사
		_materials[i].Ambient = _materials[i].Diffuse;		// 재질용 주변광 색깔 설정

		_texture[i] = nullptr;

		auto textureLoad = D3DXCreateTextureFromFileA( D3D9_DEVICE, fileName.c_str(), &_texture[i] );

		// if fail to load texture, assert
		assert( !FAILED( textureLoad ) );
	}

	return true;
}

void XMeshObject::Render()
{
	auto cameraMatrix = CameraManager::Get().GetCamera( 0 )->GetCameraMatrix(); // camera matrix
	auto effect = _shader->GetEffect(); // d3d effect

	UINT pass = 0;

	// if exist mesh and succeed shader start
	if (_mesh)
	{
		// because initialize default shader, The begin function always succeeded
		if (SUCCEEDED( effect->Begin( &pass, 0 ) ))
		{
			// start shader render
			effect->BeginPass( 0 );

			auto shaderFunc = bind(
				[&]()
				{
					if (_texture)
					{
						effect->SetTexture( "texDiffuse", *(_texture) );
						effect->SetBool( "useDiffuseTexture", true );
					}

					D3DXMATRIX mWVP, mWI, mWIT;
					mWVP = cameraMatrix->_world * _matrix->Transform() * cameraMatrix->_view * cameraMatrix->_proj;
					D3DXMatrixInverse( &mWI, NULL, &cameraMatrix->_world );
					D3DXMatrixTranspose( &mWIT, &mWI );

					effect->SetMatrix( "mWorld", &cameraMatrix->_world );
					effect->SetMatrix( "mWVP", &mWVP );
					effect->SetMatrix( "mWIT", &mWIT );

					effect->SetFloatArray( "vEye", &cameraMatrix->_eyePt.x, 3 );
					effect->CommitChanges();
				}
			);

			shaderFunc();

			// end shader render
			effect->EndPass();
		}

		for (DWORD i = 0; i < _numMaterials; i++)
		{
			if (_materials)
			{
				D3D9_DEVICE->SetMaterial( &_materials[i] );
			}

			_mesh->DrawSubset( i );
		}

		// end shader
		effect->End();
	}
}
