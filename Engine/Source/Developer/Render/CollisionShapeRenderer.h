#pragma once

#include <d3dx9.h>
#include <btBulletCollisionCommon.h>
#include <btBulletDynamicsCommon.h>
#include "D3D9Shader.h"

#define WIRE_FRAME_SHADER "C:/Users/boseul/Documents/GitHub/SE_NinetailEngine/Engine/Resource/wireframe.fx"

struct LineVertex
{
	D3DXVECTOR3 _pos;
	D3DCOLOR _diffuse;

	static DWORD GetFVF()
	{
		return D3DFVF_XYZ | D3DFVF_DIFFUSE;
	}
};

struct CollisionWireFrame
{
	btRigidBody* _rigidBody;
	DWORD _color;

	CollisionWireFrame() : _color( 0xFF0000FF )
	{

	}
};

class CollisionShapeRenderer
{
public:
	~CollisionShapeRenderer();

	static CollisionShapeRenderer* Get();

	void Render();

	void AddWireFrame( CollisionWireFrame* _wireRender );

	void SetViewProjectTM( D3DXMATRIX viewProjection )
	{
		_viewProjection = viewProjection;
	}

	void DrawGrid( float xLength, float yLength, int xGrid, int yGrid, DWORD color );

private:

	CollisionShapeRenderer();

	void CreateEffect();
	void CreateMatrixStack();

	void CreateWireBox();
	void CreateWireHalfSphere( int slices, int stacks, DWORD color );
	void CreateWireCylinder( int slices, DWORD color );
	void CreateWireCylinderClose( int slices, DWORD color );
	void CreateWireSphere( int slices, int stacks, DWORD color );

	void RenderWireRigidBody( btRigidBody *rigidBody, DWORD color );

	void RenderWireShape( const btCollisionShape* shape, DWORD color );
	void RenderWireBox( const btBoxShape* shape, DWORD color );
	void RenderWireSphere( const btSphereShape* pShape, DWORD color );
	void RenderWireHalfSphere( float radius, DWORD color );
	void RenderWireCylinderClose( const btCylinderShape* pShape, DWORD color );
	void RenderWireCylinder( float fHeight, float fRadius, DWORD color );
	void RenderWireCapsule( const btCapsuleShape* pShape, DWORD color );

private:

	ShaderPtr _shader;

	LPD3DXMATRIXSTACK _matrixStack;

	D3DXMATRIX _viewProjection;

	// box
	LPDIRECT3DVERTEXBUFFER9 _wireBoxVertexBuffer;
	LPDIRECT3DINDEXBUFFER9 _wireBoxIndexBuffer;

	// half sphere
	LPDIRECT3DVERTEXBUFFER9 _wireHalfSphereVertexBuffer;
	int _wireSphereVertex;

	// opened cylinder
	LPDIRECT3DVERTEXBUFFER9 _wireCylinderVertexBuffer;
	int _wireCylinderVertex;

	// closed cylinder
	LPDIRECT3DVERTEXBUFFER9 _wireCylinderCloseVertexBuffer;
	int _wireCylinderCloseVertex;

	// sphere
	LPDIRECT3DVERTEXBUFFER9 _wireSphereVertexBuffer;
	int _wireSphereVertexNumber;

	static CollisionShapeRenderer* _instance;

	vector<CollisionWireFrame*> _colVector;
};