#include "RenderPCH.h"
#include "XMeshAnimation.h"
#include "CreateD3D9.h"

#pragma warning ( disable : 4996 )


HRESULT BoneHierarchyLoader::CreateFrame( LPCSTR Name, LPD3DXFRAME *ppNewFrame )
{
	Bone* newBone = new Bone();

	// name 복사
	if (Name)
	{
		newBone->Name = new char[ strlen( Name ) + 1 ];
		strcpy( newBone->Name, Name );
	}

	// initialization
	D3DXMatrixIdentity( &newBone->TransformationMatrix );
	D3DXMatrixIdentity( &newBone->_combinedTransMatrix );

	// return new bone
	*ppNewFrame = static_cast<D3DXFRAME*>(newBone);

	return S_OK;
}

HRESULT BoneHierarchyLoader::CreateMeshContainer( LPCSTR Name,
												  CONST D3DXMESHDATA *pMeshData,
												  CONST D3DXMATERIAL *pMaterials,
												  CONST D3DXEFFECTINSTANCE *pEffectInstances,
												  DWORD NumMaterials,
												  CONST DWORD *pAdjacency,
												  LPD3DXSKININFO pSkinInfo,
												  LPD3DXMESHCONTAINER *ppNewMeshContainer )
{
	BoneMesh* boneMesh = new BoneMesh();

	// 메시 데이터를 얻는다.
	// 소프트웨어 스키닝을 위해서는 메시의 원본 형태의 데이터를 보관해두어야한다.
	boneMesh->_originalMesh = pMeshData->pMesh;
	boneMesh->MeshData.pMesh = pMeshData->pMesh;
	boneMesh->MeshData.Type = pMeshData->Type;

	// 메시의 메모리가 해제되지 않도록 참조값을 증가시킨다
	pMeshData->pMesh->AddRef();

	LPDIRECT3DDEVICE9 device = nullptr;
	pMeshData->pMesh->GetDevice( &device );

	// materials, texture
	//for (int i = 0; i < NumMaterials; i++)
	//{
	//	D3DXMATERIAL mtrl;
	//	memcpy(&mtrl, &pMaterials[i], sizeof(D3DXMATERIAL));
	//	boneMesh->_materials.push_back(mtrl.MatD3D);

	//	IDirect3DTexture9* newTexture = nullptr;

	//	if (mtrl.pTextureFilename != nullptr)
	//	{
	//		char texFileName[200] = "";
	//		strcat(texFileName, mtrl.pTextureFilename);

	//		D3DXCreateTextureFromFile(device, texFileName, &newTexture);
	//	}

	//	boneMesh->_textures.push_back(newTexture);
	//}

	if (pSkinInfo != nullptr)
	{
		boneMesh->pSkinInfo = pSkinInfo;

		pSkinInfo->AddRef();

		pMeshData->pMesh->CloneMeshFVF( D3DXMESH_MANAGED,
										pMeshData->pMesh->GetFVF(),
										device,
										&boneMesh->MeshData.pMesh );

		boneMesh->MeshData.pMesh->GetAttributeTable( nullptr, &boneMesh->_numAttributeGroups );
		boneMesh->_attributeTable = new D3DXATTRIBUTERANGE[ boneMesh->_numAttributeGroups ];
		boneMesh->MeshData.pMesh->GetAttributeTable( boneMesh->_attributeTable, nullptr );

		int numBones = pSkinInfo->GetNumBones();
		boneMesh->_boneOffsetMatrices = new D3DXMATRIX[ numBones ];
		boneMesh->_currentBoneMatrices = new D3DXMATRIX[ numBones ];

		for (int i = 0; i < numBones; i++)
		{
			boneMesh->_boneOffsetMatrices[ i ] = *(boneMesh->pSkinInfo->GetBoneOffsetMatrix( i ));
		}
	}

	*ppNewMeshContainer = boneMesh;

	return S_OK;
}


HRESULT BoneHierarchyLoader::DestroyFrame( LPD3DXFRAME pFrameToFree )
{
	if (pFrameToFree)
	{
		if (pFrameToFree->Name)
		{
			delete[] pFrameToFree->Name;
		}

		delete pFrameToFree;
	}

	pFrameToFree = nullptr;

	return S_OK;
}

HRESULT BoneHierarchyLoader::DestroyMeshContainer( LPD3DXMESHCONTAINER pMeshContainerToFree )
{
	if (pMeshContainerToFree)
	{
		delete pMeshContainerToFree;
	}

	return S_OK;
}

void SkinnedMesh::Load( const string& fileName )
{

	BoneHierarchyLoader boneHierarchy;

	// .x 파일로부터 본 계층 구조를 로드한다.
	auto hr = D3DXLoadMeshHierarchyFromX( fileName.c_str(), D3DXMESH_MANAGED, D3D9_DEVICE, &boneHierarchy,
										  NULL, &_rootBone, &_animation );

	if (FAILED( hr ))
	{
		// assert
	}

	// bone matrices update
	SetMatrices();

	UpdateMatrices( static_cast<Bone*>(_rootBone), &_world );

	SetupBoneMatrixPtr( static_cast<Bone*>(_rootBone) );

	// render sphere
	D3DXCreateSphere( D3D9_DEVICE, 2.0f, 10, 10, &_sphereMesh, NULL );

}

void SkinnedMesh::UpdateMatrices( Bone* bone, D3DXMATRIX* parentMatrix )
{
	if (!bone)
	{
		// assert
	}

	// 부모 변환 행렬과 복합된 월드 변환 행렬을 계산
	D3DXMatrixMultiply( &bone->_combinedTransMatrix, &bone->TransformationMatrix, parentMatrix );

	// 동일한 계산을 형제 본에도 수행
	if (bone->pFrameSibling)
	{
		UpdateMatrices( static_cast<Bone*>(bone->pFrameSibling), parentMatrix );
	}

	// 동일한 계산을 자식 본에 수행
	if (bone->pFrameFirstChild)
	{
		UpdateMatrices( static_cast<Bone*>(bone->pFrameFirstChild), &bone->_combinedTransMatrix );
	}

	_world = *parentMatrix;
}

void SkinnedMesh::SetupBoneMatrixPtr( const Bone* bone )
{
	if (bone->pMeshContainer)
	{
		BoneMesh* boneMesh = static_cast<BoneMesh*>(bone->pMeshContainer);

		if (boneMesh->pSkinInfo)
		{
			int numBones = boneMesh->pSkinInfo->GetNumBones();

			boneMesh->_boneMatrixPtrs = new D3DXMATRIX*[ numBones ];

			// 각 본마다 행렬 적용
			for (int i = 0; i < numBones; i++)
			{
				auto newBone = static_cast<Bone*>(D3DXFrameFind( _rootBone, boneMesh->pSkinInfo->GetBoneName( i ) ));

				if (newBone)
				{
					boneMesh->_boneMatrixPtrs[ i ] = &newBone->_combinedTransMatrix;
				}

				else
				{
					boneMesh->_boneMatrixPtrs[ i ] = nullptr;
				}
			}
		}
	}

	if (bone->pFrameSibling)
	{
		SetupBoneMatrixPtr( static_cast<Bone*>(bone->pFrameSibling) );
	}

	if (bone->pFrameFirstChild)
	{
		SetupBoneMatrixPtr( static_cast<Bone*>(bone->pFrameFirstChild) );
	}
}


void SkinnedMesh::RenderSkeleton( Bone* bone /* = nullptr */, Bone* parent /* = nullptr */ )
{
	SetMatrices();

	if (!bone)
	{
		bone = static_cast<Bone*>(_rootBone);
	}

	if (!parent)
	{
		parent = static_cast<Bone*>(_rootBone);
	}

	D3DXMATRIX r, s, t;
	D3DXMatrixRotationYawPitchRoll( &r, -D3DX_PI * 0.5f, 0.0f, 0.0f );

	if (parent && bone->Name && parent->Name)
	{
		// 본의 위치에 원을 그린다
		s = r * bone->_combinedTransMatrix * _world;
		D3DXMatrixTranslation( &t, s( 3, 0 ), s( 3, 1 ), s( 3, 2 ) );

		D3D9_DEVICE->SetTransform( D3DTS_WORLD, &t );
		_sphereMesh->DrawSubset( 0 );

		// 본 사이에 라인을 그린다
		D3D9_DEVICE->SetRenderState( D3DRS_LIGHTING, true );

		D3DXMATRIX w1 = bone->_combinedTransMatrix;
		D3DXMATRIX w2 = parent->_combinedTransMatrix;

		D3DXVECTOR3 thisBone = D3DXVECTOR3( w1( 3, 0 ), w1( 3, 1 ), w1( 3, 2 ) );
		D3DXVECTOR3 parentBone = D3DXVECTOR3( w2( 3, 0 ), w2( 3, 1 ), w2( 3, 2 ) );

		D3D9_DEVICE->SetTransform( D3DTS_WORLD, &_world );
		Vertex vert[] = { Vertex( parentBone, 0xffff0000 ), Vertex( thisBone, 0xff00ff00 ) };

		D3D9_DEVICE->SetRenderState( D3DRS_LIGHTING, false );
		D3D9_DEVICE->SetFVF( D3DFVF_XYZ | D3DFVF_DIFFUSE );
		D3D9_DEVICE->DrawPrimitiveUP( D3DPT_LINESTRIP, 1, &vert[ 0 ], sizeof( Vertex ) );
	}

	D3D9_DEVICE->SetTransform( D3DTS_WORLD, &_world );

	if (bone->pFrameSibling)
	{
		RenderSkeleton( static_cast<Bone*>(bone->pFrameSibling), parent );
	}

	if (bone->pFrameFirstChild)
	{
		RenderSkeleton( static_cast<Bone*>(bone->pFrameFirstChild), bone );
	}
}


void SkinnedMesh::Render( const Bone* bone /* = nullptr */ )
{
	SetMatrices();

	if (!bone)
	{
		bone = static_cast<Bone*>(_rootBone);
	}

	if (bone->pMeshContainer)
	{
		BoneMesh* boneMesh = static_cast<BoneMesh*>(_rootBone->pMeshContainer);

		if (boneMesh->pSkinInfo)
		{
			int numBones = boneMesh->pSkinInfo->GetNumBones();

			for (int i = 0; i < numBones; i++)
			{
				D3DXMatrixMultiply( &boneMesh->_currentBoneMatrices[ i ],
									&boneMesh->_boneOffsetMatrices[ i ],
									boneMesh->_boneMatrixPtrs[ i ] );
			}

			BYTE* src = nullptr;
			BYTE* dest = nullptr;

			boneMesh->_originalMesh->LockVertexBuffer( D3DLOCK_READONLY, (void**)&src );
			boneMesh->MeshData.pMesh->LockVertexBuffer( 0, (void**)&dest );

			boneMesh->pSkinInfo->UpdateSkinnedMesh( boneMesh->_currentBoneMatrices,
													nullptr,
													src,
													dest );

			boneMesh->MeshData.pMesh->UnlockVertexBuffer();
			boneMesh->_originalMesh->UnlockVertexBuffer();

			for (int i = 0; i < boneMesh->_numAttributeGroups; i++)
			{
				int mtrl = boneMesh->_attributeTable[ i ].AttribId;

				//_device->SetMaterial(&(boneMesh->_materials[mtrl]));
				//_device->SetTexture(0, boneMesh->_textures[mtrl]);
				boneMesh->MeshData.pMesh->DrawSubset( mtrl );
			}
		}
	}

	if (bone->pFrameSibling)
	{
		Render( static_cast<Bone*>(bone->pFrameSibling) );
	}

	if (bone->pFrameFirstChild)
	{
		Render( static_cast<Bone*>(bone->pFrameFirstChild) );
	}
}

void SkinnedMesh::SetAnimation( int getAnimNum, int setTrackNum )
{
	// set animation
	ID3DXAnimationSet* animSet;

	_animation->GetAnimationSet( getAnimNum, &animSet );

	_animation->SetTrackAnimationSet( setTrackNum, animSet );

	animSet->Release();
}

void SkinnedMesh::SetPose( float time )
{
	if (_animation != NULL)
	{
		_animation->AdvanceTime( time, NULL );
	}

	UpdateMatrices( static_cast<Bone*>(_rootBone), &_world );
}