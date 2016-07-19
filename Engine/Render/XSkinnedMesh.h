#pragma once

#include "XMeshObject.h"
#include "XBoneHierarchyLoader.h"

class XSkinnedMesh;

using XAnimatedObjectPtr = shared_ptr< XSkinnedMesh >;

class XSkinnedMesh : public XMeshObject
{
public:

	XSkinnedMesh();
	virtual ~XSkinnedMesh();

	static XAnimatedObjectPtr Create( const string& fileName );

	// Load data
	virtual void LoadModel( const string& fileName );

	virtual void LoadTexture( const string& fileName );

	// Render
	//void RenderSkeleton( Bone* bone = nullptr, Bone* parent = nullptr );

	virtual void Render();

	void Render( const BoneFrame* bone );

	// Animation
	void SetAnimation( int getAnimNum, int setTrackNum );

	void SetPose( float time );

private:

	void SetMatrices() { D3DXMatrixIdentity( &_world ); }

	void UpdateMatrices( Bone* bone, D3DXMATRIX* parentMatrix );

	void SetupBoneMatrixPtr( const BoneFrame* bone );

private:

	//D3DXFRAME* _rootBone;
	Bone* _rootBone;

	D3DXMATRIX _world;

	LPD3DXANIMATIONCONTROLLER _animation;

	//vector<D3DMATERIAL9> _materials;
	IDirect3DTexture9* _texture;

private:

	// Related to create skeleton
	//LPD3DXMESH _sphereMesh;
};
//
//struct Vertex
//{
//	Vertex() {}
//
//	Vertex( D3DXVECTOR3 pos, D3DCOLOR color ) : _pos( pos ), _color( color ) {}
//
//	D3DXVECTOR3 _pos;
//	D3DCOLOR _color;
//};
