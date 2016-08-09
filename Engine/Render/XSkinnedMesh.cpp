#include "RenderPCH.h"
#include "XSkinnedMesh.h"
#include "CreateD3D9.h"
#include "CameraManager.h"

XSkinnedMesh::XSkinnedMesh()
{
}


XSkinnedMesh::~XSkinnedMesh()
{
}

XAnimatedObjectPtr XSkinnedMesh::Create( const string& fileName )
{
	XAnimatedObjectPtr animatedObj( new XSkinnedMesh() );

	animatedObj->LoadModel( fileName );

	return animatedObj;
}


void XSkinnedMesh::LoadModel( const string& fileName )
{
	BoneHierarchyLoader boneHierarchy;

	BoneFrame* frame = nullptr;

	// .x 파일로부터 본 계층 구조를 로드한다.
	auto hr = D3DXLoadMeshHierarchyFromX( fileName.c_str(), D3DXMESH_MANAGED, D3D9_DEVICE, &boneHierarchy, NULL,
										  &frame, &_animation );

	if (FAILED( hr ))
	{
		SAFE_DELETE( frame );
		// assert
	}

	_rootBone = static_cast<Bone*>(frame);

	// bone matrices update
	SetMatrices();

	UpdateMatrices( _rootBone, &_world );

	SetupBoneMatrixPtr( _rootBone );

	// render sphere
	//D3DXCreateSphere( D3D9_DEVICE, 2.0f, 10, 10, &_sphereMesh, NULL );

	//LoadTexture( DEFAULT_TEX );

}

void XSkinnedMesh::LoadTexture( const string& fileName )
{
	//// materials
	//D3DXMATERIAL mtrl;
	//memcpy( &mtrl, &pMaterials[i], sizeof( D3DXMATERIAL ) );
	//_materials.push_back( mtrl.MatD3D );

	// texture
	D3DXCreateTextureFromFile( D3D9_DEVICE, fileName.c_str(), &_texture );

}

//
//void XSkinnedMesh::RenderSkeleton( Bone* bone /* = nullptr */, Bone* parent /* = nullptr */ )
//{
//	SetMatrices();
//
//	if (!bone)
//	{
//		bone = _rootBone;
//	}
//
//	if (!parent)
//	{
//		parent = _rootBone;
//	}
//
//	D3DXMATRIX r, s, t;
//	D3DXMatrixRotationYawPitchRoll( &r, -D3DX_PI * 0.5f, 0.0f, 0.0f );
//
//	if (parent && bone->Name && parent->Name)
//	{
//		// 본의 위치에 원을 그린다
//		s = r * bone->_combinedTransMatrix * _world;
//		D3DXMatrixTranslation( &t, s( 3, 0 ), s( 3, 1 ), s( 3, 2 ) );
//
//		D3D9_DEVICE->SetTransform( D3DTS_WORLD, &t );
//		_sphereMesh->DrawSubset( 0 );
//
//		// 본 사이에 라인을 그린다
//		D3D9_DEVICE->SetRenderState( D3DRS_LIGHTING, true );
//
//		D3DXMATRIX w1 = bone->_combinedTransMatrix;
//		D3DXMATRIX w2 = parent->_combinedTransMatrix;
//
//		D3DXVECTOR3 thisBone = D3DXVECTOR3( w1( 3, 0 ), w1( 3, 1 ), w1( 3, 2 ) );
//		D3DXVECTOR3 parentBone = D3DXVECTOR3( w2( 3, 0 ), w2( 3, 1 ), w2( 3, 2 ) );
//
//		D3D9_DEVICE->SetTransform( D3DTS_WORLD, &_world );
//		Vertex vert[] = { Vertex( parentBone, 0xffff0000 ), Vertex( thisBone, 0xff00ff00 ) };
//
//		D3D9_DEVICE->SetRenderState( D3DRS_LIGHTING, false );
//		D3D9_DEVICE->SetFVF( D3DFVF_XYZ | D3DFVF_DIFFUSE );
//		D3D9_DEVICE->DrawPrimitiveUP( D3DPT_LINESTRIP, 1, &vert[0], sizeof( Vertex ) );
//	}
//
//	D3D9_DEVICE->SetTransform( D3DTS_WORLD, &_world );
//
//	if (bone->pFrameSibling)
//	{
//		RenderSkeleton( static_cast<Bone*>(bone->pFrameSibling), parent );
//	}
//
//	if (bone->pFrameFirstChild)
//	{
//		RenderSkeleton( static_cast<Bone*>(bone->pFrameFirstChild), bone );
//	}
//}

void XSkinnedMesh::Render()
{
	Render( _rootBone );

	D3D9_DEVICE->SetTransform( D3DTS_WORLD, &_matrix->Transform() );

	auto cameraMatrix = CameraManager::Get()->GetCamera( 0 )->GetCameraMatrix(); // camera matrix
	auto effect = _shader->GetEffect(); // d3d effect
	UINT pass = 0;

	//// because initialize default shader, The begin function always succeeded
	//if (SUCCEEDED( effect->Begin( &pass, 0 ) ))
	//{
	//	// start shader render
	//	effect->BeginPass( 0 );

	//	// shader
	//	// 모델에 셰이더랑 크기가 적용이 안됨
	//	auto shaderFunc = bind(
	//		[&]()
	//		{
	//			if (_texture)
	//			{
	//				effect->SetTexture( "texDiffuse", (_texture) );
	//				effect->SetBool( "useDiffuseTexture", true );
	//			}

	//			D3DXMATRIX mWVP, mWI, mWIT;
	//			mWVP = cameraMatrix->_world * _matrix->Transform() * cameraMatrix->_view * cameraMatrix->_proj;
	//			D3DXMatrixInverse( &mWI, NULL, &cameraMatrix->_world );
	//			D3DXMatrixTranspose( &mWIT, &mWI );

	//			effect->SetMatrix( "mWorld", &cameraMatrix->_world );
	//			effect->SetMatrix( "mWVP", &mWVP );
	//			effect->SetMatrix( "mWIT", &mWIT );

	//			effect->SetFloatArray( "vEye", &cameraMatrix->_eyePt.x, 3 );
	//			effect->CommitChanges();
	//		}
	//	);

	//	shaderFunc();

	//	// end shader render
	//	effect->EndPass();

	//	// end shader
	//	effect->End();
	//}
}

void XSkinnedMesh::Render( const BoneFrame* bone /* = nullptr */ )
{
	SetMatrices();

	if (!bone)
	{
		bone = _rootBone;
	}

	if (bone->pMeshContainer)
	{
		BoneMesh* boneMesh = static_cast<BoneMesh*>(_rootBone->pMeshContainer);

		if (boneMesh->pSkinInfo)
		{
			int numBones = boneMesh->pSkinInfo->GetNumBones();

			for (int i = 0; i < numBones; i++)
			{
				D3DXMatrixMultiply( &boneMesh->_currentBoneMatrices[i],
									&boneMesh->_boneOffsetMatrices[i],
									boneMesh->_boneMatrixPtrs[i] );
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
				int mtrl = boneMesh->_attributeTable[i].AttribId;

				D3D9_DEVICE->SetMaterial(&(boneMesh->_materials[mtrl]));
				D3D9_DEVICE->SetTexture( 0, _texture );

				boneMesh->MeshData.pMesh->DrawSubset( mtrl );
			}
		}
	}

	if (bone->pFrameSibling)
	{
		Render( bone->pFrameSibling );
	}

	if (bone->pFrameFirstChild)
	{
		Render( bone->pFrameFirstChild );
	}
}

void XSkinnedMesh::SetAnimation( int getAnimNum, int setTrackNum )
{
	// set animation
	ID3DXAnimationSet* animSet;

	_animation->GetAnimationSet( getAnimNum, &animSet );

	_animation->SetTrackAnimationSet( setTrackNum, animSet );

	animSet->Release();
}

void XSkinnedMesh::SetPose( float time )
{
	if (_animation != NULL)
	{
		_animation->AdvanceTime( time, NULL );
	}

	UpdateMatrices( _rootBone, &_world );
}

void XSkinnedMesh::UpdateMatrices( Bone* bone, D3DXMATRIX* parentMatrix )
{
	if (!bone)
	{
		// assert
		return;
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

void XSkinnedMesh::SetupBoneMatrixPtr( const BoneFrame* bone )
{
	if (bone->pMeshContainer)
	{
		BoneMesh* boneMesh = static_cast<BoneMesh*>(bone->pMeshContainer);

		if (boneMesh->pSkinInfo)
		{
			int numBones = boneMesh->pSkinInfo->GetNumBones();

			boneMesh->_boneMatrixPtrs = new D3DXMATRIX*[numBones];

			// 각 본마다 행렬 적용
			for (int i = 0; i < numBones; i++)
			{
				auto newBone = static_cast<Bone*>(D3DXFrameFind( _rootBone, boneMesh->pSkinInfo->GetBoneName( i ) ));

				if (newBone)
				{
					boneMesh->_boneMatrixPtrs[i] = &newBone->_combinedTransMatrix;
				}

				else
				{
					boneMesh->_boneMatrixPtrs[i] = nullptr;
				}
			}
		}
	}

	if (bone->pFrameSibling)
	{
		SetupBoneMatrixPtr( bone->pFrameSibling );
	}

	if (bone->pFrameFirstChild)
	{
		SetupBoneMatrixPtr( bone->pFrameFirstChild );
	}
}
