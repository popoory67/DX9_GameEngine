#pragma once

#include "Matrix.h"

struct Bone : public D3DXFRAME
{
	D3DXMATRIX	_combinedTransMatrix;	// 해당 본의 실제 월드 변환 정보를 담음
};

struct BoneMesh : public D3DXMESHCONTAINER
{
	ID3DXMesh* _originalMesh;
	//vector<D3DMATERIAL9> _materials;
	//vector<IDirect3DTexture9*> _textures;

	DWORD _numAttributeGroups;
	D3DXATTRIBUTERANGE* _attributeTable;
	D3DXMATRIX** _boneMatrixPtrs;
	D3DXMATRIX* _boneOffsetMatrices;
	D3DXMATRIX* _currentBoneMatrices;
};

// Use ID3DXAllocateHierarchy interface.
class BoneHierarchyLoader : public ID3DXAllocateHierarchy
{

public:

	BoneHierarchyLoader() {}
	~BoneHierarchyLoader() {}

	// ID3DXAllocateHierarchy's virtual functions.
	STDMETHOD( CreateFrame )(THIS_ LPCSTR Name, LPD3DXFRAME *ppNewFrame);

	STDMETHOD( CreateMeshContainer )(THIS_ LPCSTR Name,
									  CONST D3DXMESHDATA *pMeshData,
									  CONST D3DXMATERIAL *pMaterials,
									  CONST D3DXEFFECTINSTANCE *pEffectInstances,
									  DWORD NumMaterials,
									  CONST DWORD *pAdjacency,
									  LPD3DXSKININFO pSkinInfo,
									  LPD3DXMESHCONTAINER *ppNewMeshContainer);

	STDMETHOD( DestroyFrame )(THIS_ LPD3DXFRAME pFrameToFree);

	STDMETHOD( DestroyMeshContainer )(THIS_ LPD3DXMESHCONTAINER pMeshContainerToFree);

};


class SkinnedMesh
{
public:

	SkinnedMesh() { _matrix = new Matrix(); }
	~SkinnedMesh() { delete(_matrix); }

	void Load( const string& fileName );

	void RenderSkeleton( Bone* bone = nullptr, Bone* parent = nullptr );

	void Render( const Bone* bone = nullptr );

	void SetAnimation( int getAnimNum, int setTrackNum );

	void SetPose( float time );

	Matrix* GetMatrix() const { return _matrix; }

private:

	void SetMatrices() { D3DXMatrixIdentity( &_world ); }

	void UpdateMatrices( Bone* bone, D3DXMATRIX* parentMatrix );

	void SetupBoneMatrixPtr( const Bone* bone );

private:

	Matrix* _matrix;

	D3DXFRAME* _rootBone;

	D3DXMATRIX _world;

	LPD3DXANIMATIONCONTROLLER _animation;

private:

	LPD3DXMESH _sphereMesh;
};

struct Vertex
{
	Vertex() {}

	Vertex( D3DXVECTOR3 pos, D3DCOLOR color ) : _pos( pos ), _color( color ) {}

	D3DXVECTOR3 _pos;
	D3DCOLOR _color;
};
