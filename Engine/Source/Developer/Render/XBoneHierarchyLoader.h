#pragma once

#include <vector>
#include <d3dx9.h>

using BoneFrame = D3DXFRAME;

struct Bone : public D3DXFRAME
{
	D3DXMATRIX				_combinedTransMatrix;	// 해당 본의 실제 월드 변환 정보를 담음
};

struct BoneMesh : public D3DXMESHCONTAINER
{
	ID3DXMesh*				_originalMesh;
	vector<D3DMATERIAL9>	_materials;
	//vector<IDirect3DTexture9*> _textures;

	DWORD					_numAttributeGroups;
	D3DXATTRIBUTERANGE*		_attributeTable;
	D3DXMATRIX**			_boneMatrixPtrs;
	D3DXMATRIX*				_boneOffsetMatrices;
	D3DXMATRIX*				_currentBoneMatrices;
};

// Use ID3DXAllocateHierarchy interface.
class BoneHierarchyLoader : public ID3DXAllocateHierarchy
{
public:

	BoneHierarchyLoader()	{}
	~BoneHierarchyLoader()	{}

	// ID3DXAllocateHierarchy's virtual functions.
	STDMETHOD( CreateFrame )(THIS_ LPCSTR Name, LPD3DXFRAME *ppNewFrame);

	STDMETHOD( CreateMeshContainer )( THIS_ LPCSTR Name,
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