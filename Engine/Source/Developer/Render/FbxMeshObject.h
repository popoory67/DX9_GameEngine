#pragma once

#include <d3d11.h>
#include "FbxLoader.h"

using namespace FbxLoader;

using DXFLOAT4 = DirectX::XMFLOAT4;
using DXFLOAT3 = DirectX::XMFLOAT3;
using DXFLOAT2 = DirectX::XMFLOAT2;

struct VertexData
{
	DXFLOAT3 _pos;
	DXFLOAT3 _normal;
	DXFLOAT2 _texcoord;
};

struct FbxMaterialData
{
	DXFLOAT4 _ambient;
	DXFLOAT4 _diffuse;
	DXFLOAT4 _specular;
	DXFLOAT4 _emmisive;
};

struct FbxMaterial
{
	FbxMaterialData _materialData;

	float _specularPower;
	float _transparencyFactor;

	ID3D11ShaderResourceView* _shaderRV;
	ID3D11SamplerState* _sampler;
	ID3D11Buffer* _materialBuffer;

	FbxMaterial() : _shaderRV( nullptr ), _sampler( nullptr ), _materialBuffer( nullptr )
	{

	}

	~FbxMaterial()
	{
		Release();
	}

	void Release()
	{
		if (_materialBuffer)
		{
			SAFE_RELEASE( _materialBuffer );
		}

		if (_shaderRV)
		{
			SAFE_RELEASE( _shaderRV );
		}

		if (_sampler)
		{
			SAFE_RELEASE( _sampler );
		}
	}
};

struct MeshNode
{
	ID3D11Buffer* _VB;
	ID3D11Buffer* _IB;
	ID3D11InputLayout* _inputLayout;

	DWORD _vertexCount;
	DWORD _indexCount;

	FbxMaterial _materialData;

	float _mat4x4[16];

	// INDEX BUFFER BIT
	enum IndexBit
	{
		INDEX_NOINDEX = 0,
		INDEX_16BIT,		// 16bit
		INDEX_32BIT,		// 32bit
	};
	IndexBit _indexBit;

	MeshNode() :
		_VB( nullptr ),
		_IB( nullptr ),
		_inputLayout( nullptr ),
		_indexBit( INDEX_NOINDEX ),
		_vertexCount( 0 ),
		_indexCount( 0 )
	{

	}

	~MeshNode()
	{
		Release();
	}

	void Release()
	{
		_materialData.Release();

		if (_inputLayout)
		{
			SAFE_RELEASE( _inputLayout );
		}
		if (_IB)
		{
			SAFE_RELEASE( _IB );
		}
		if (_VB)
		{
			SAFE_RELEASE( _VB );
		}
	}

	void SetIndexBit( const size_t indexCount )
	{
		_indexBit = INDEX_NOINDEX;

		if (indexCount != 0)
		{
			_indexBit = INDEX_32BIT;
		}
	};
};

class CFBXRenderDX11
{
	CFBXLoader*		m_pFBX;

	std::vector<MeshNode>	m_meshNodeArray;

	HRESULT CreateNodes( const bool isOptimize );
	HRESULT VertexConstruction( FBX_MESH_NODE &fbxNode, MeshNode& meshNode );
	HRESULT VertexConstructionWithOptimize( FBX_MESH_NODE &fbxNode, MeshNode& meshNode );
	HRESULT MaterialConstruction( FBX_MESH_NODE &fbxNode, MeshNode& meshNode );

	HRESULT CreateVertexBuffer(  ID3D11Buffer** pBuffer, void* pVertices, uint32_t stride, uint32_t vertexCount );
	HRESULT CreateIndexBuffer(  ID3D11Buffer** pBuffer, void* pIndices, uint32_t indexCount );

public:
	CFBXRenderDX11();
	~CFBXRenderDX11();

	void Release();

	HRESULT LoadFBX( const char* filename, const bool isOptimize = true );
	HRESULT CreateInputLayout( const void* pShaderBytecodeWithInputSignature, size_t BytecodeLength, D3D11_INPUT_ELEMENT_DESC* pLayout, unsigned int layoutSize );

	HRESULT RenderAll( );
	HRESULT RenderNode( const size_t nodeId );
	HRESULT RenderNodeInstancing( const size_t nodeId, const uint32_t InstanceCount );
	HRESULT RenderNodeInstancingIndirect( const size_t nodeId, ID3D11Buffer* pBufferForArgs, const uint32_t AlignedByteOffsetForArgs );

	size_t GetNodeCount() { return m_meshNodeArray.size(); }

	MeshNode& GetNode( const int id ) { return m_meshNodeArray[id]; };
	void	GetNodeMatrix( const int id, float* mat4x4 ) { memcpy( mat4x4, m_meshNodeArray[id]._mat4x4, sizeof( float ) * 16 ); };
	FbxMaterial& GetNodeMaterial( const size_t id ) { return m_meshNodeArray[id]._materialData; };
};

//class FbxMeshObject
//{
//public:
//	FbxMeshObject();
//	~FbxMeshObject();
//};
//
