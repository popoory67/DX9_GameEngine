#pragma once

#include "XBoneHierarchyLoader.h"

class XSkinnedMesh;

using XAnimatedObjectPtr = shared_ptr<XSkinnedMesh>;

class XSkinnedMesh
{
public:

	XSkinnedMesh();
	~XSkinnedMesh();

	void Load( const string& fileName );

	void RenderSkeleton( Bone* bone = nullptr, Bone* parent = nullptr );

	void Render( const BoneFrame* bone = nullptr );

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

private:

	// Related to create skeleton
	LPD3DXMESH _sphereMesh;
};

struct Vertex
{
	Vertex() {}

	Vertex( D3DXVECTOR3 pos, D3DCOLOR color ) : _pos( pos ), _color( color ) {}

	D3DXVECTOR3 _pos;
	D3DCOLOR _color;
};
