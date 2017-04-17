#include "RenderPCH.h"
#include "FbxMeshObject.h"
#include "DDSTextureLoader.h"
#include <DirectXMesh.h>
#include "D3D11Device.h"
#include <locale.h>

//FbxMeshObject::FbxMeshObject()
//{
//}
//
//
//FbxMeshObject::~FbxMeshObject()
//{
//}


CFBXRenderDX11::CFBXRenderDX11()
{
	m_pFBX = nullptr;
}

CFBXRenderDX11::~CFBXRenderDX11()
{
	Release();
}

void CFBXRenderDX11::Release()
{
	for (size_t i = 0; i < m_meshNodeArray.size(); i++)
	{
		m_meshNodeArray[i].Release();
	}
	m_meshNodeArray.clear();

	if (m_pFBX)
	{
		delete m_pFBX;
		m_pFBX = nullptr;
	}
}

HRESULT CFBXRenderDX11::LoadFBX( const char* filename, const bool isOptimize )
{
	if (!filename)
		return E_FAIL;

	HRESULT hr = S_OK;

	m_pFBX = new CFBXLoader;
	hr = m_pFBX->LoadFBX( filename, CFBXLoader::eAXIS_OPENGL );
	if (FAILED( hr ))
		return hr;

	hr = CreateNodes( isOptimize );
	if (FAILED( hr ))
		return hr;

	return hr;
}

//
HRESULT CFBXRenderDX11::CreateNodes( const bool isOptimize )
{
	HRESULT hr = S_OK;

	size_t nodeCoount = m_pFBX->GetNodesCount();
	if (nodeCoount == 0)
		return E_FAIL;

	for (size_t i = 0; i < nodeCoount; i++)
	{
		MeshNode meshNode;
		FBX_MESH_NODE fbxNode = m_pFBX->GetNode( static_cast<unsigned int>(i) );

		if (isOptimize)
		{
			// 最適化あり
			VertexConstructionWithOptimize( fbxNode, meshNode );
		}
		else
		{
			// 最適化なし
			VertexConstruction( fbxNode, meshNode );

			// index buffer
			meshNode._indexCount = static_cast<DWORD>(fbxNode.indexArray.size());
			meshNode.SetIndexBit( meshNode._indexCount );
			if (fbxNode.indexArray.size() > 0)
				hr = CreateIndexBuffer( &meshNode._IB, &fbxNode.indexArray[0], static_cast<uint32_t>(fbxNode.indexArray.size()) );
		}

		memcpy( meshNode._mat4x4, fbxNode.mat4x4, sizeof( float ) * 16 );

		// ?テリアル
		MaterialConstruction( fbxNode, meshNode );

		m_meshNodeArray.push_back( meshNode );
	}


	return hr;
}

HRESULT CFBXRenderDX11::VertexConstructionWithOptimize( FBX_MESH_NODE &fbxNode, MeshNode& meshNode )
{
	HRESULT hr = S_OK;
	size_t nFaces = fbxNode.indexArray.size() / 3;
	size_t nVerts = fbxNode.m_positionArray.size();

	if (nFaces == 0 || nVerts == 0)
		return S_OK;

	VertexData*	pIn = new VertexData[nVerts];

	meshNode._vertexCount = static_cast<DWORD>(nVerts);
	for (size_t i = 0; i < meshNode._vertexCount; i++)
	{
		FbxVector4 v = fbxNode.m_positionArray[i];
		pIn[i]._pos = DirectX::XMFLOAT3( (float)v.mData[0],
										 (float)v.mData[1],
										 (float)v.mData[2] );

		v = fbxNode.m_normalArray[i];

		pIn[i]._normal = DirectX::XMFLOAT3( (float)v.mData[0],
										 (float)v.mData[1],
										 (float)v.mData[2] );

		if ((float)fbxNode.m_texcoordArray.size() > 0)
		{
			// 今回はUV1つしかやらない
			// UVのV値反?
			pIn[i]._texcoord = DirectX::XMFLOAT2( (float)abs( 1.0f - fbxNode.m_texcoordArray[i].mData[0] ),
												  (float)abs( 1.0f - fbxNode.m_texcoordArray[i].mData[1] ) );
		}
		else
			pIn[i]._texcoord = DirectX::XMFLOAT2( 0, 0 );
	}

	// 最適化
	uint32_t* indecies = new uint32_t[fbxNode.indexArray.size()];
	if (fbxNode.indexArray.size() > 0)
	{
		memcpy( indecies, &fbxNode.indexArray.front(), sizeof( uint32_t )*fbxNode.indexArray.size() );
	}
	DirectX::XMFLOAT3* pos = new DirectX::XMFLOAT3[nVerts];
	for (size_t j = 0; j < nVerts; ++j)
		pos[j] = DirectX::XMFLOAT3( static_cast<float>(fbxNode.m_positionArray[j].mData[0]), static_cast<float>(fbxNode.m_positionArray[j].mData[1]), static_cast<float>(fbxNode.m_positionArray[j].mData[2]) );

	uint32_t* adj = new uint32_t[fbxNode.indexArray.size()];

	hr = DirectX::GenerateAdjacencyAndPointReps( indecies, nFaces, pos, nVerts, 0.f, nullptr, adj );
	if (FAILED( hr ))
	{
		delete indecies;

		delete adj;
		return hr;
	}

	uint32_t* faceRemap = new uint32_t[nFaces];
	hr = DirectX::OptimizeFaces( indecies, nFaces, adj, faceRemap );
	if (FAILED( hr ))
	{
		delete indecies;

		delete adj;
		delete faceRemap;
		return hr;
	}

	uint32_t* newIndices = new uint32_t[nFaces * 3];
	hr = DirectX::ReorderIB( indecies, nFaces, faceRemap, newIndices );
	if (FAILED( hr ))
	{
		delete indecies;

		delete adj;
		delete faceRemap;
		delete newIndices;
		return hr;
	}

	uint32_t* vertRemap = new uint32_t[nVerts];
	hr = DirectX::OptimizeVertices( newIndices, nFaces, nVerts, vertRemap );
	if (FAILED( hr ))
	{
		delete indecies;

		delete adj;
		delete faceRemap;
		delete newIndices;
		delete vertRemap;
		return hr;
	}
	
	hr = DirectX::FinalizeIB( newIndices, nFaces, vertRemap, nVerts );
	if (FAILED( hr ))
		return hr;

	VertexData*	pOut = new VertexData[nVerts];

	hr = DirectX::FinalizeVB( pIn, sizeof( VertexData ), nVerts, nullptr, 0, vertRemap, pOut );

	CreateVertexBuffer( &meshNode._VB, pOut, sizeof( VertexData ), meshNode._vertexCount );

	// index buffer
	meshNode._indexCount = static_cast<DWORD>(nFaces * 3);
	meshNode.SetIndexBit( meshNode._indexCount );
	if (fbxNode.indexArray.size() > 0)
		hr = CreateIndexBuffer( &meshNode._IB, newIndices, static_cast<uint32_t>(nFaces * 3) );

	delete indecies;

	delete adj;
	delete faceRemap;
	delete newIndices;
	delete vertRemap;
	return hr;

}

HRESULT CFBXRenderDX11::CreateVertexBuffer( ID3D11Buffer** pBuffer, void* pVertices, uint32_t stride, uint32_t vertexCount )
{
	if ( stride == 0 || vertexCount == 0)
		return E_FAIL;

	HRESULT hr = S_OK;

	D3D11_BUFFER_DESC bd;
	ZeroMemory( &bd, sizeof( bd ) );
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = stride * vertexCount;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = 0;
	D3D11_SUBRESOURCE_DATA InitData;
	ZeroMemory( &InitData, sizeof( InitData ) );

	InitData.pSysMem = pVertices;

	hr = D3D11_DEVICE->CreateBuffer( &bd, &InitData, pBuffer );
	if (FAILED( hr ))
		return hr;

	return hr;
}

HRESULT CFBXRenderDX11::CreateIndexBuffer( ID3D11Buffer** pBuffer, void* pIndices, uint32_t indexCount )
{
	if ( indexCount == 0)
		return E_FAIL;

	HRESULT hr = S_OK;
	size_t stride = sizeof( unsigned int );

	D3D11_BUFFER_DESC bd;
	ZeroMemory( &bd, sizeof( bd ) );
	bd.Usage = D3D11_USAGE_DYNAMIC;
	bd.ByteWidth = static_cast<uint32_t>(stride*indexCount);
	bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
	bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	D3D11_SUBRESOURCE_DATA InitData;
	ZeroMemory( &InitData, sizeof( InitData ) );

	InitData.pSysMem = pIndices;

	hr = D3D11_DEVICE->CreateBuffer( &bd, &InitData, pBuffer );
	if (FAILED( hr ))
		return hr;

	return hr;
}


HRESULT CFBXRenderDX11::VertexConstruction( FBX_MESH_NODE &fbxNode, MeshNode& meshNode )
{
	meshNode._vertexCount = static_cast<DWORD>(fbxNode.m_positionArray.size());
	if (meshNode._vertexCount == 0)
		return E_FAIL;

	HRESULT hr = S_OK;


	VertexData*	pV = new VertexData[meshNode._vertexCount];

	//	const size_t numUVSet = fbxNode.m_texcoordArray.size();

	for (size_t i = 0; i < meshNode._vertexCount; i++)
	{
		FbxVector4 v = fbxNode.m_positionArray[i];
		pV[i]._pos = DirectX::XMFLOAT3( (float)v.mData[0],
										(float)v.mData[1],
										(float)v.mData[2] );

		v = fbxNode.m_normalArray[i];

		pV[i]._normal = DirectX::XMFLOAT3( (float)v.mData[0],
										(float)v.mData[1],
										(float)v.mData[2] );

		if ((float)fbxNode.m_texcoordArray.size() > 0)
		{
			// 今回はUV1つしかやらない
			// UVのV値反?
			pV[i]._texcoord = DirectX::XMFLOAT2( (float)abs( 1.0f - fbxNode.m_texcoordArray[i].mData[0] ),
												 (float)abs( 1.0f - fbxNode.m_texcoordArray[i].mData[1] ) );
		}
		else
			pV[i]._texcoord = DirectX::XMFLOAT2( 0, 0 );
	}

	CreateVertexBuffer(&meshNode._VB, pV, sizeof( VertexData ), meshNode._vertexCount );

	if (pV)
		delete[] pV;

	return hr;
}

//
HRESULT CFBXRenderDX11::MaterialConstruction( FBX_MESH_NODE &fbxNode, MeshNode& meshNode )
{
	if ( fbxNode.m_materialArray.size() == 0)
		return E_FAIL;

	HRESULT hr = S_OK;

	// 今回は先頭の?テリアルだけ使う
	FBX_MATERIAL_NODE fbxMaterial = fbxNode.m_materialArray[0];
	meshNode._materialData._specularPower = fbxMaterial.shininess;
	meshNode._materialData._transparencyFactor = fbxMaterial.TransparencyFactor;

	meshNode._materialData._materialData._ambient
		= DirectX::XMFLOAT4( fbxMaterial.ambient.r, fbxMaterial.ambient.g, fbxMaterial.ambient.b, fbxMaterial.ambient.a );
	meshNode._materialData._materialData._diffuse
		= DirectX::XMFLOAT4( fbxMaterial.diffuse.r, fbxMaterial.diffuse.g, fbxMaterial.diffuse.b, fbxMaterial.diffuse.a );
	meshNode._materialData._materialData._specular
		= DirectX::XMFLOAT4( fbxMaterial.specular.r, fbxMaterial.specular.g, fbxMaterial.specular.b, fbxMaterial.specular.a );
	meshNode._materialData._materialData._emmisive
		= DirectX::XMFLOAT4( fbxMaterial.emmisive.r, fbxMaterial.emmisive.g, fbxMaterial.emmisive.b, fbxMaterial.emmisive.a );


	// Diffuseだけからテクス?ャを読み込む
	if (fbxMaterial.diffuse.textureSetArray.size() > 0)
	{
		TextureSet::const_iterator it = fbxMaterial.diffuse.textureSetArray.begin();
		if (it->second.size())
		{
			std::string path = it->second[0];

			// June 2010の時から変更
			//			hr = D3DX11CreateShaderResourceViewFromFileA( pd3dDevice,path.c_str(), NULL, NULL, &meshNode.materialData.pSRV, NULL );

			// Todo: 決め打ちよくないけど暫定対応
			// FBXのSDKだと文字列はcharなんだけど、こっちではwcharにしないといけない...
			WCHAR	wstr[512];
			size_t wLen = 0;
			mbstowcs_s( &wLen, wstr, path.size() + 1, path.c_str(), _TRUNCATE );
			CreateDDSTextureFromFile( D3D11_DEVICE, wstr, NULL, &meshNode._materialData._shaderRV, 0 );	// DXTexから
		}
	}

	// samplerstate
	D3D11_SAMPLER_DESC sampDesc;
	ZeroMemory( &sampDesc, sizeof( sampDesc ) );
	sampDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	sampDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	sampDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	sampDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	sampDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
	sampDesc.MinLOD = 0;
	sampDesc.MaxLOD = D3D11_FLOAT32_MAX;
	hr = D3D11_DEVICE->CreateSamplerState( &sampDesc, &meshNode._materialData._sampler );

	// material Constant Buffer
	D3D11_BUFFER_DESC bufDesc;
	ZeroMemory( &bufDesc, sizeof( bufDesc ) );
	bufDesc.ByteWidth = sizeof( FbxMaterialData );
	bufDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	bufDesc.CPUAccessFlags = 0;

	hr = D3D11_DEVICE->CreateBuffer( &bufDesc, NULL, &meshNode._materialData._materialBuffer );

	//meshNode.materialData.materialConstantData.ambient = meshNode.materialData.ambient;
	//meshNode.materialData.materialConstantData.diffuse = meshNode.materialData.ambient;
	//meshNode.materialData.materialConstantData.specular = meshNode.materialData.specular;
	//meshNode.materialData.materialConstantData.emmisive = meshNode.materialData.emmisive;

	return hr;
}

//
HRESULT CFBXRenderDX11::CreateInputLayout( const void* pShaderBytecodeWithInputSignature, size_t BytecodeLength, D3D11_INPUT_ELEMENT_DESC* pLayout, unsigned int layoutSize )
{
	if (!pShaderBytecodeWithInputSignature || !pLayout)
		return E_FAIL;

	HRESULT hr = S_OK;

	for (auto meshNode = m_meshNodeArray.begin(); meshNode != m_meshNodeArray.end(); ++meshNode)
	{
		hr = D3D11_DEVICE->CreateInputLayout( pLayout, layoutSize, pShaderBytecodeWithInputSignature, BytecodeLength, &meshNode->_inputLayout );
	}

	return hr;
}

HRESULT CFBXRenderDX11::RenderAll( )
{
	size_t nodeCount = m_meshNodeArray.size();
	if (nodeCount == 0)
		return S_OK;

	HRESULT hr = S_OK;

	D3D11_DEVICE_CONTEXT->IASetPrimitiveTopology( D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST );

	for (auto meshNode = m_meshNodeArray.begin(); meshNode != m_meshNodeArray.end(); ++meshNode)
	{
		if (meshNode->_vertexCount == 0)
			continue;

		UINT stride = sizeof( VertexData );
		UINT offset = 0;
		D3D11_DEVICE_CONTEXT->IASetVertexBuffers( 0, 1, &meshNode->_VB, &stride, &offset );

		DXGI_FORMAT indexbit = DXGI_FORMAT_R16_UINT;
		if (meshNode->_indexBit == MeshNode::INDEX_32BIT)
			indexbit = DXGI_FORMAT_R32_UINT;

		D3D11_DEVICE_CONTEXT->IASetInputLayout( meshNode->_inputLayout );
		D3D11_DEVICE_CONTEXT->IASetIndexBuffer( meshNode->_IB, indexbit, 0 );

		D3D11_DEVICE_CONTEXT->DrawIndexed( meshNode->_indexCount, 0, 0 );
	}

	return hr;
}

HRESULT CFBXRenderDX11::RenderNode(const size_t nodeId )
{
	size_t nodeCount = m_meshNodeArray.size();
	if (nodeCount == 0 || nodeCount <= nodeId)
		return S_OK;

	HRESULT hr = S_OK;

	MeshNode* node = &m_meshNodeArray[nodeId];

	if (node->_vertexCount == 0)
		return S_OK;

	UINT stride = sizeof( VertexData );
	UINT offset = 0;
	D3D11_DEVICE_CONTEXT->IASetVertexBuffers( 0, 1, &node->_VB, &stride, &offset );
	D3D11_DEVICE_CONTEXT->IASetInputLayout( node->_inputLayout );
	D3D11_DEVICE_CONTEXT->IASetPrimitiveTopology( D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST );

	// インデックスバッフ?が存在する場合
	if (node->_indexBit != MeshNode::INDEX_NOINDEX)
	{
		DXGI_FORMAT indexbit = DXGI_FORMAT_R16_UINT;
		if (node->_indexBit == MeshNode::INDEX_32BIT)
			indexbit = DXGI_FORMAT_R32_UINT;

		D3D11_DEVICE_CONTEXT->IASetIndexBuffer( node->_IB, indexbit, 0 );

		D3D11_DEVICE_CONTEXT->DrawIndexed( node->_indexCount, 0, 0 );
	}

	return hr;
}

HRESULT CFBXRenderDX11::RenderNodeInstancing( const size_t nodeId, const uint32_t InstanceCount )
{
	size_t nodeCount = m_meshNodeArray.size();
	if (nodeCount == 0 || nodeCount <= nodeId || InstanceCount == 0)
		return S_OK;

	HRESULT hr = S_OK;

	MeshNode* node = &m_meshNodeArray[nodeId];

	if (node->_vertexCount == 0)
		return S_OK;

	UINT stride = sizeof( VertexData );
	UINT offset = 0;
	D3D11_DEVICE_CONTEXT->IASetVertexBuffers( 0, 1, &node->_VB, &stride, &offset );
	D3D11_DEVICE_CONTEXT->IASetInputLayout( node->_inputLayout );
	D3D11_DEVICE_CONTEXT->IASetPrimitiveTopology( D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST );

	// インデックスバッフ?が存在する場合
	if (node->_indexBit != MeshNode::INDEX_NOINDEX)
	{
		DXGI_FORMAT indexbit = DXGI_FORMAT_R16_UINT;
		if (node->_indexBit == MeshNode::INDEX_32BIT)
			indexbit = DXGI_FORMAT_R32_UINT;

		D3D11_DEVICE_CONTEXT->IASetIndexBuffer( node->_IB, indexbit, 0 );

		D3D11_DEVICE_CONTEXT->DrawIndexedInstanced( node->_indexCount, InstanceCount, 0, 0, 0 );
	}

	return hr;
}

HRESULT CFBXRenderDX11::RenderNodeInstancingIndirect( const size_t nodeId, ID3D11Buffer* pBufferForArgs, const uint32_t AlignedByteOffsetForArgs )
{
	size_t nodeCount = m_meshNodeArray.size();
	if (nodeCount == 0 || nodeCount <= nodeId)
		return S_OK;

	HRESULT hr = S_OK;

	MeshNode* node = &m_meshNodeArray[nodeId];

	if (node->_vertexCount == 0)
		return S_OK;

	UINT stride = sizeof( VertexData );
	UINT offset = 0;
	D3D11_DEVICE_CONTEXT->IASetVertexBuffers( 0, 1, &node->_VB, &stride, &offset );
	D3D11_DEVICE_CONTEXT->IASetInputLayout( node->_inputLayout );
	D3D11_DEVICE_CONTEXT->IASetPrimitiveTopology( D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST );

	// インデックスバッフ?が存在する場合
	if (node->_indexBit != MeshNode::INDEX_NOINDEX)
	{
		DXGI_FORMAT indexbit = DXGI_FORMAT_R16_UINT;
		if (node->_indexBit == MeshNode::INDEX_32BIT)
			indexbit = DXGI_FORMAT_R32_UINT;

		D3D11_DEVICE_CONTEXT->IASetIndexBuffer( node->_IB, indexbit, 0 );

		D3D11_DEVICE_CONTEXT->DrawIndexedInstancedIndirect( pBufferForArgs, AlignedByteOffsetForArgs );
	}

	return hr;
}
