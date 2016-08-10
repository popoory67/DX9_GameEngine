#include "RenderPCH.h"
#include "XBoneHierarchyLoader.h"

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
	*ppNewFrame = newBone;

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
	for (int i = 0; i < NumMaterials; i++)
	{
		D3DXMATERIAL mtrl;
		memcpy(&mtrl, &pMaterials[i], sizeof(D3DXMATERIAL));
		boneMesh->_materials.push_back(mtrl.MatD3D);

		/*IDirect3DTexture9* newTexture = nullptr;

		if (mtrl.pTextureFilename != nullptr)
		{
			char texFileName[200] = "";
			strcat(texFileName, mtrl.pTextureFilename);

			D3DXCreateTextureFromFile(device, texFileName, &newTexture);
		}

		boneMesh->_textures.push_back(newTexture);*/
	}

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
	SAFE_DELETE_ARRAY( pFrameToFree->Name );

	SAFE_DELETE( pFrameToFree );

	return S_OK;
}

HRESULT BoneHierarchyLoader::DestroyMeshContainer( LPD3DXMESHCONTAINER pMeshContainerToFree )
{
	SAFE_DELETE( pMeshContainerToFree );

	return S_OK;
}