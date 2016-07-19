#include "RenderPCH.h"
#include "ObjMeshObject.h"

#include "RenderMacros.h"
#include "CreateD3D9.h"
#include "CameraManager.h"

#include "Util.h"


ObjMeshObject::ObjMeshObject()
{

}

ObjMeshObject::~ObjMeshObject()
{
	SAFE_RELEASE( _VB );
}


// this structure describes a face vertex in an obj mesh
struct ObjTriVertex
{
	int _pos = -1;
	int _normal = -1;
	int _tex = -1;
};

// this structure describes a triangle in the obj mesh.
struct ObjTriangle
{
	ObjTriVertex vertex[ 3 ];
};

using ObjTriangleList = vector< ObjTriangle >;

// adds an .obj face to the specified triangle list. 
// If the face is not triangular, it is triangulated by taking, for the (n)th vertex, 
// where n starts from 2, the triangle that consists of the first vertex, the (n)th vertex, and the (n-1)th vertex.
void AddObjFace( ObjTriangleList& objTriangleList, const ObjMesh& objMesh, UINT objFaceIndex, bool flipTriangles, bool flipUVs )
{
	const ObjMesh::Face& objFace = objMesh._faces[ objFaceIndex ];

	UINT triCount = objFace._verticesCount - 2;

	for (int fv = 2; fv < objFace._verticesCount; fv++)
	{
		ObjTriangle tri;

		tri.vertex[ 0 ]._pos = objMesh._faceVertices[ objFace._firstVertex ];
		tri.vertex[ 1 ]._pos = objMesh._faceVertices[ objFace._firstVertex + fv - 1 ];
		tri.vertex[ 2 ]._pos = objMesh._faceVertices[ objFace._firstVertex + fv ];

# ifdef DEBUG
		if (tri.vertex[0]._pos >= objMesh.vertices.Size()) DebugBreak();
		if (tri.vertex[1]._pos >= objMesh.vertices.Size()) DebugBreak();
		if (tri.vertex[2]._pos >= objMesh.vertices.Size()) DebugBreak();
# endif


		if (!objMesh._normals.empty() && objFace._firstNormal >= 0)
		{
			tri.vertex[ 0 ]._normal = objMesh._faceNormals[ objFace._firstNormal ];
			tri.vertex[ 1 ]._normal = objMesh._faceNormals[ objFace._firstNormal + fv - 1 ];
			tri.vertex[ 2 ]._normal = objMesh._faceNormals[ objFace._firstNormal + fv ];
# ifdef DEBUG
			if (tri.vertex[0]._normal >= objMesh.normals.Size()) DebugBreak();
			if (tri.vertex[1]._normal >= objMesh.normals.Size()) DebugBreak();
			if (tri.vertex[2]._normal >= objMesh.normals.Size()) DebugBreak();
# endif
		}

		if (!objMesh._texCoords.empty() && objFace._firstTexCoord >= 0)
		{
			tri.vertex[ 0 ]._tex = objMesh._faceTexCoords[ objFace._firstTexCoord ];
			tri.vertex[ 1 ]._tex = objMesh._faceTexCoords[ objFace._firstTexCoord + fv - 1 ];
			tri.vertex[ 2 ]._tex = objMesh._faceTexCoords[ objFace._firstTexCoord + fv ];
		}

		objTriangleList.push_back( tri );
	}
}


ObjMeshPtr ObjMeshObject::Create( const string& fileName )
{
	ObjMeshPtr objMesh( new ObjMeshObject() );

	objMesh->LoadModel( fileName );

	return objMesh;
}

void ObjMeshObject::LoadModel( const string& fileName )
{
	shared_ptr<ObjMesh> objMesh( new ObjMesh() );

	// .obj 데이터를 받아옴
	if (ObjLoader::LoadObj( fileName, objMesh.get() ) < 0)
	{
		assert( Util::Error( "Failed to load the obj file" ) );
	}

	// 메시 생성
	auto objMeshLoad = FAILED( Init( *objMesh, false, true ) );

	// assert
	assert( !objMeshLoad );
}


void ObjMeshObject::LoadTexture( const string& fileName )
{
	auto textureLoad = FAILED( D3DXCreateTextureFromFile( D3D9_DEVICE, fileName.c_str(), &_texture ) );

	// if fail to load texture,  assert
	assert( !textureLoad );

}

void ObjMeshObject::Render()
{
	auto cameraMatrix = CameraManager::Get().GetCamera( 0 )->GetCameraMatrix(); // camera matrix
	auto effect = _shader->GetEffect(); // d3d effect

	UINT pass = 0;

	// shader
	if (SUCCEEDED( effect->Begin( &pass, 0 ) ))
	{
		effect->BeginPass( 0 );

		if (_texture)
		{
			effect->SetTexture( "texDiffuse", _texture );
			effect->SetBool( "useDiffuseTexture", true );
		}

		D3DXMATRIX mWVP, mWI, mWIT;
		mWVP = cameraMatrix->_world * _matrix->Transform() * cameraMatrix->_view * cameraMatrix->_proj;
		D3DXMatrixInverse( &mWI, NULL, &cameraMatrix->_world );
		D3DXMatrixTranspose( &mWIT, &mWI );

		effect->SetMatrix( "mWorld", &cameraMatrix->_world );
		effect->SetMatrix( "mWVP", &mWVP );
		effect->SetMatrix( "mWIT", &mWIT );

		effect->SetFloatArray( "vEye", &cameraMatrix->_eyePt.x, 3 );
		effect->CommitChanges();

		effect->EndPass();
	}

	// mesh render
	//D3D9_DEVICE->SetTransform(D3DTS_WORLD, &matrix->Transform());
	D3D9_DEVICE->SetStreamSource( 0, _VB, 0, _vertexSize );
	D3D9_DEVICE->SetFVF( _FVF );
	D3D9_DEVICE->DrawPrimitive( D3DPT_TRIANGLELIST, 0, _triCount );

	// end shader
	effect->End();

}


HRESULT ObjMeshObject::Init( const ObjMesh& objMesh, bool flipTriangles, bool flipUVs )
{
	if (objMesh._vertices.empty() || objMesh._numTriangles == 0)
	{
		OutputDebugString( TEXT( __FUNCTION__ )TEXT( ": obj mesh is invalid!" ) );

		return E_FAIL;
	}

	_bbmin = objMesh._bbmin;
	_bbmax = objMesh._bbmax;

	return InitVB( objMesh, flipTriangles, flipUVs );
}


HRESULT ObjMeshObject::InitVB( const ObjMesh& objMesh, bool flipTriangles, bool flipUVs )
{
	HRESULT hr;

	SAFE_RELEASE( _VB );

	_vertexSize = sizeof( D3DXVECTOR3 ); // Has at least positional data.

	_FVF = D3DFVF_XYZ;

	BOOL hasNormals = TRUE;// We'll compute them when needed. !objMesh.normals.empty();
	BOOL hasTexCoords = !objMesh._texCoords.empty();

	if (hasNormals)
	{
		_vertexSize += sizeof( D3DXVECTOR3 );

		_FVF |= D3DFVF_NORMAL;
	}

	if (hasTexCoords)
	{
		_vertexSize += sizeof( D3DXVECTOR2 );

		_FVF |= (D3DFVF_TEX2 | D3DFVF_TEXCOORDSIZE2( 0 ));
	}


	ObjTriangleList triList;

	triList.reserve( objMesh._numTriangles );

	for (UINT i = 0; i < objMesh._faces.size(); i++)
	{
		AddObjFace( triList, objMesh, i, FALSE, FALSE );
	}

	_triCount = triList.size();

	struct VBVertex
	{
		D3DXVECTOR3 pos;
		D3DXVECTOR3 normal;
		D3DXVECTOR2 tex;
	};

	UINT bufferSize = _triCount * _vertexSize * 3;

	hr = D3D9_DEVICE->CreateVertexBuffer( bufferSize, D3DUSAGE_WRITEONLY, 
										  _FVF, D3DPOOL_DEFAULT, &_VB, NULL );

	if (FAILED( hr ))
	{
		return hr;
	}

	BYTE* pVBData = NULL;

	hr = _VB->Lock( 0, 0, (VOID**)&pVBData, 0 );

	if (FAILED( hr ))
	{
		return hr;
	}

	UINT vertexOrder[] = { 0, 1, 2 };

	if (flipTriangles)
	{
		vertexOrder[ 1 ] = 2; vertexOrder[ 2 ] = 1;
	}

	for (UINT i = 0; i < triList.size(); i++)
	{
		ObjTriangle& tri = triList[ i ];

		// Compute the triangle's normal if the obj mesh does not have normals info.
		D3DXVECTOR3 triNormal;

		if (tri.vertex[ 0 ]._normal < 0)
		{
			D3DXVECTOR3 vec1 = objMesh._vertices[ tri.vertex[ 2 ]._pos ] - objMesh._vertices[ tri.vertex[ 0 ]._pos ];
			D3DXVECTOR3 vec2 = objMesh._vertices[ tri.vertex[ 2 ]._pos ] - objMesh._vertices[ tri.vertex[ 1 ]._pos ];

			if (flipTriangles)
			{
				D3DXVec3Cross( &triNormal, &vec2, &vec1 );
			}

			else
			{
				D3DXVec3Cross( &triNormal, &vec1, &vec2 );
			}

			D3DXVec3Normalize( &triNormal, &triNormal );
		}

		for (UINT tv = 0; tv < 3; tv++)
		{
			UINT v = vertexOrder[ tv ];

			VBVertex* pVBVertex = (VBVertex*)pVBData;

			pVBVertex->pos = objMesh._vertices[ tri.vertex[ v ]._pos ];

			if (tri.vertex[ v ]._normal < 0)
			{
				pVBVertex->normal = triNormal;
			}

			else
			{
				pVBVertex->normal = objMesh._normals[ tri.vertex[ v ]._normal ];
			}

			if (hasTexCoords && tri.vertex[ v ]._tex >= 0)
			{
				if (flipUVs)
				{
					D3DXVECTOR2 tex = objMesh._texCoords[ tri.vertex[ v ]._tex ];
					tex.y = 1 - tex.y;
					pVBVertex->tex = tex;
				}

				else
				{
					pVBVertex->tex = objMesh._texCoords[ tri.vertex[ v ]._tex ];
				}
			}

			pVBData += _vertexSize;
		}
	}

	_VB->Unlock();

	return S_OK;
}