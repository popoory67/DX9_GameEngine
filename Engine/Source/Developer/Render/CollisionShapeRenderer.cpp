#include "RenderPCH.h"
#include "CollisionShapeRenderer.h"
#include "D3D9Device.h"
#include "CameraManager.h"


#define INDEX_SIZE		24


CollisionShapeRenderer* CollisionShapeRenderer::_instance = nullptr;


D3DXMATRIX btTransformToD3DXMATIRX( const btTransform& transform )
{
	btVector3 R = transform.getBasis().getColumn( 0 );
	btVector3 U = transform.getBasis().getColumn( 1 );
	btVector3 L = transform.getBasis().getColumn( 2 );
	btVector3 P = transform.getOrigin();

	D3DXMATRIX mat;
	mat._11 = R.m_floats[0]; mat._12 = R.m_floats[1]; mat._13 = R.m_floats[2]; mat._14 = 0.f;
	mat._21 = U.m_floats[0]; mat._22 = U.m_floats[1]; mat._23 = U.m_floats[2]; mat._24 = 0.f;
	mat._31 = L.m_floats[0]; mat._32 = L.m_floats[1]; mat._33 = L.m_floats[2]; mat._34 = 0.f;
	mat._41 = P.m_floats[0]; mat._42 = P.m_floats[1]; mat._43 = P.m_floats[2]; mat._44 = 1.f;

	return mat;
}

CollisionShapeRenderer::CollisionShapeRenderer()
{
	_shader = D3D9Shader::Create();

	_colVector.clear();
	_dynamicColList.clear();

	CreateMatrixStack();
	CreateEffect();
}

CollisionShapeRenderer::~CollisionShapeRenderer()
{
	SAFE_RELEASE( _matrixStack );

	SAFE_RELEASE( _wireBoxVertexBuffer );
	SAFE_RELEASE( _wireBoxIndexBuffer );

	SAFE_RELEASE( _wireHalfSphereVertexBuffer );
	SAFE_RELEASE( _wireCylinderVertexBuffer );
	SAFE_RELEASE( _wireCylinderCloseVertexBuffer );
	SAFE_RELEASE( _wireSphereVertexBuffer );

	SAFE_DELETE( _instance );
}

CollisionShapeRenderer* CollisionShapeRenderer::Get()
{
	if (!_instance)
	{
		_instance = new CollisionShapeRenderer();
	}

	return _instance;
}

void CollisionShapeRenderer::AddWireFrame( CollisionWireFrame* _wireRender )
{
	_colVector.push_back( _wireRender );
}

void CollisionShapeRenderer::AddDynamicWireFrame( CollisionWireFrame* _wireRender )
{
	_dynamicColList.push_back( _wireRender );
}


void CollisionShapeRenderer::RemoveWireFrame( CollisionWireFrame* _wireRender )
{
	for (auto iter = _colVector.begin(); iter != _colVector.end();)
	{
		if (*iter == _wireRender)
		{
			SAFE_DELETE( *iter );
			iter = _colVector.erase( iter );

			return;
		}
		iter++;
	}
}

void CollisionShapeRenderer::RemoveDynamicWireFrame( CollisionWireFrame* _wireRender )
{
	for (auto iter = _dynamicColList.begin(); iter != _dynamicColList.end(); iter++)
	{
		if (*iter == _wireRender)
		{
			SAFE_DELETE( *iter );

			_dynamicColList.remove( *iter );
		}
	}
}

void CollisionShapeRenderer::Render()
{
	if (_dynamicColList.size() > 5)
	{
		_dynamicColList.pop_front();
	}

	for (auto iter = _dynamicColList.begin(); iter != _dynamicColList.end(); iter++)
	{
		auto cameraMatrix = CameraManager::Get().GetCamera( 0 )->GetCameraMatrix();
		auto mat = cameraMatrix._view * cameraMatrix._proj;
		SetViewProjectTM( mat );
		RenderWireRigidBody( (*iter)->_rigidBody, (*iter)->_color );
	}

	for (auto iter = _colVector.begin(); iter != _colVector.end(); iter++)
	{
		auto cameraMatrix = CameraManager::Get().GetCamera( 0 )->GetCameraMatrix();
		auto mat = cameraMatrix._view * cameraMatrix._proj;
		SetViewProjectTM( mat );
		RenderWireRigidBody( (*iter)->_rigidBody, (*iter)->_color );
	}
}

void CollisionShapeRenderer::CreateEffect()
{
	_shader->LoadShader( WIRE_FRAME_SHADER );

	_shader->GetEffect()->SetTechnique( "TShader" );
}

void CollisionShapeRenderer::CreateMatrixStack()
{
	D3DXCreateMatrixStack( 0, &_matrixStack );
	_matrixStack->LoadIdentity();
}

void CollisionShapeRenderer::CreateWireBox()
{
	int vertexNumber = 8;
	int vertexListSize = vertexNumber * sizeof( LineVertex );

	LineVertex* vertex = new LineVertex[vertexNumber];

	DWORD color = D3DCOLOR_COLORVALUE( 0.0f, 0.0f, 0.0f, 1.0f );

	D3D9_DEVICE->CreateVertexBuffer( vertexListSize, 0, D3DFVF_XYZ | D3DFVF_DIFFUSE,
									 D3DPOOL_MANAGED, &_wireBoxVertexBuffer, NULL );

	vertex[0]._pos.x = -1.0f; 
	vertex[0]._pos.y = 1.0f; 
	vertex[0]._pos.z = -1.0f; 
	vertex[0]._diffuse = color;

	vertex[1]._pos.x = -1.0f; 
	vertex[1]._pos.y = -1.0f; 
	vertex[1]._pos.z = -1.0f; 
	vertex[1]._diffuse = color;

	vertex[2]._pos.x = 1.0f; 
	vertex[2]._pos.y = -1.0f; 
	vertex[2]._pos.z = -1.0f;
	vertex[2]._diffuse = color;

	vertex[3]._pos.x = 1.0f; 
	vertex[3]._pos.y = 1.0f; 
	vertex[3]._pos.z = -1.0f; 
	vertex[3]._diffuse = color;

	vertex[4]._pos.x = -1.0f; 
	vertex[4]._pos.y = 1.0f; 
	vertex[4]._pos.z = 1.0f; 
	vertex[4]._diffuse = color;

	vertex[5]._pos.x = -1.0f; 
	vertex[5]._pos.y = -1.0f; 
	vertex[5]._pos.z = 1.0f; 
	vertex[5]._diffuse = color;

	vertex[6]._pos.x = 1.0f; 
	vertex[6]._pos.y = -1.0f;
	vertex[6]._pos.z = 1.0f; 
	vertex[6]._diffuse = color;

	vertex[7]._pos.x = 1.0f; 
	vertex[7]._pos.y = 1.0f; 
	vertex[7]._pos.z = 1.0f; 
	vertex[7]._diffuse = color;

	VOID* vertices = NULL;

	_wireBoxVertexBuffer->Lock( 0, 0, (void**)&vertices, NULL );
	memcpy( vertices, vertex, vertexListSize );
	_wireBoxVertexBuffer->Unlock();

	SAFE_DELETE_ARRAY( vertex );

	D3D9_DEVICE->CreateIndexBuffer( 12 * sizeof( unsigned short ) * 2, 0, D3DFMT_INDEX16,
									D3DPOOL_MANAGED, &_wireBoxIndexBuffer, NULL );

	unsigned short index[INDEX_SIZE] = { 0, 1, 1, 2, 2, 3, 3, 0, 4, 5, 5, 6, 6, 7, 7, 4, 0, 4, 1, 5, 2, 6, 3, 7 };
	unsigned short* indices;

	_wireBoxIndexBuffer->Lock( 0, 0, (void **)&indices, NULL );
	memcpy( indices, index, sizeof( unsigned short ) * INDEX_SIZE );
	_wireBoxIndexBuffer->Unlock();
}


void CollisionShapeRenderer::CreateWireHalfSphere( int slices, int stacks, DWORD color )
{
	int i, j;
	int vertexNumber = 0;
	int vertexCount;
	float thetaStep;
	float phiStep;
	LineVertex* vertex;

	thetaStep = (3.141592f * 0.5f) / stacks;
	phiStep = (3.141592f * 2.0f) / slices;

	vertexNumber = (stacks - 1)*slices * 6 + 3 * slices;

	_wireSphereVertex = vertexNumber;

	vertex = new LineVertex[vertexNumber];

	int vertListSize = sizeof( LineVertex ) * vertexNumber;

	D3D9_DEVICE->CreateVertexBuffer( vertListSize, 0, D3DFVF_XYZ | D3DFVF_DIFFUSE,
									 D3DPOOL_MANAGED, &_wireHalfSphereVertexBuffer, NULL );
	vertexCount = 0;

	for (i = 0; i < slices; i += 1)
	{
		for (j = 0; j < stacks; j += 1)
		{
			vertex[vertexCount]._pos.x = sinf( thetaStep*j )*cosf( phiStep*i );	
			vertex[vertexCount]._pos.y = sinf( thetaStep*j )*sinf( phiStep*i );	
			vertex[vertexCount]._pos.z = cosf( thetaStep*j );
			vertex[vertexCount]._diffuse = color;
			vertexCount += 1;

			vertex[vertexCount]._pos.x = sinf( thetaStep*(j + 1) )*cosf( phiStep*i );	
			vertex[vertexCount]._pos.y = sinf( thetaStep*(j + 1) )*sinf( phiStep*i );	
			vertex[vertexCount]._pos.z = cosf( thetaStep*(j + 1) );
			vertex[vertexCount]._diffuse = color;
			vertexCount += 1;

			vertex[vertexCount]._pos.x = sinf( thetaStep*(j + 1) )*cosf( phiStep*(i + 1) );
			vertex[vertexCount]._pos.y = sinf( thetaStep*(j + 1) )*sinf( phiStep*(i + 1) );	
			vertex[vertexCount]._pos.z = cosf( thetaStep*(j + 1) );
			vertex[vertexCount]._diffuse = color;
			vertexCount += 1;

			if (j != 0)
			{
				vertex[vertexCount]._pos.x = sinf( thetaStep*j )*cosf( phiStep*i );	
				vertex[vertexCount]._pos.y = sinf( thetaStep*j )*sinf( phiStep*i );	
				vertex[vertexCount]._pos.z = cosf( thetaStep*j );
				vertex[vertexCount]._diffuse = color;
				vertexCount += 1;

				vertex[vertexCount]._pos.x = sinf( thetaStep*(j + 1) )*cosf( phiStep*(i + 1) );
				vertex[vertexCount]._pos.y = sinf( thetaStep*(j + 1) )*sinf( phiStep*(i + 1) );	
				vertex[vertexCount]._pos.z = cosf( thetaStep*(j + 1) );
				vertex[vertexCount]._diffuse = color;
				vertexCount += 1;

				vertex[vertexCount]._pos.x = sinf( thetaStep*j )*cosf( phiStep*(i + 1) );	
				vertex[vertexCount]._pos.y = sinf( thetaStep*j )*sinf( phiStep*(i + 1) );	
				vertex[vertexCount]._pos.z = cosf( thetaStep*j );
				vertex[vertexCount]._diffuse = color;
				vertexCount += 1;
			}
		}
	}

	VOID *verts = NULL;

	_wireHalfSphereVertexBuffer->Lock( 0, 0, (void**)&verts, NULL );


	memcpy( verts, vertex, vertListSize );
	_wireHalfSphereVertexBuffer->Unlock();

	delete[] vertex;
}

void CollisionShapeRenderer::CreateWireCylinder( int slices, DWORD color )
{
	int i;
	int vertexNumber = 0;
	int vertexCount;
	float phiStep;
	LineVertex* vertex;

	phiStep = (3.141592f * 2.0f) / slices;

	vertexNumber = slices * 6;

	_wireCylinderVertex = vertexNumber;

	vertex = new LineVertex[vertexNumber];

	int vertListSize = sizeof( LineVertex ) * vertexNumber;

	D3D9_DEVICE->CreateVertexBuffer( vertListSize, 0, D3DFVF_XYZ | D3DFVF_DIFFUSE,
									 D3DPOOL_MANAGED, &_wireCylinderVertexBuffer, NULL );
	vertexCount = 0;

	for (i = 0; i < slices; i += 1)
	{
		vertex[vertexCount]._pos.x = cosf( phiStep*i );	
		vertex[vertexCount]._pos.y = sinf( phiStep*i );	
		vertex[vertexCount]._pos.z = 1.0f;
		vertex[vertexCount]._diffuse = color;
		vertexCount += 1;

		vertex[vertexCount]._pos.x = cosf( phiStep*i );	
		vertex[vertexCount]._pos.y = sinf( phiStep*i );	
		vertex[vertexCount]._pos.z = -1.0f;
		vertex[vertexCount]._diffuse = color;
		vertexCount += 1;

		vertex[vertexCount]._pos.x = cosf( phiStep*(i + 1) );	
		vertex[vertexCount]._pos.y = sinf( phiStep*(i + 1) );	
		vertex[vertexCount]._pos.z = 1.0f;
		vertex[vertexCount]._diffuse = color;
		vertexCount += 1;

		vertex[vertexCount]._pos.x = cosf( phiStep*(i + 1) );	
		vertex[vertexCount]._pos.y = sinf( phiStep*(i + 1) );	
		vertex[vertexCount]._pos.z = 1.0f;
		vertex[vertexCount]._diffuse = color;
		vertexCount += 1;

		vertex[vertexCount]._pos.x = cosf( phiStep*i ); 
		vertex[vertexCount]._pos.y = sinf( phiStep*i ); 
		vertex[vertexCount]._pos.z = -1.0f;
		vertex[vertexCount]._diffuse = color;
		vertexCount += 1;

		vertex[vertexCount]._pos.x = cosf( phiStep*(i + 1) ); 
		vertex[vertexCount]._pos.y = sinf( phiStep*(i + 1) ); 
		vertex[vertexCount]._pos.z = -1.0f;
		vertex[vertexCount]._diffuse = color;
		vertexCount += 1;

	}

	VOID *verts = NULL;

	_wireCylinderVertexBuffer->Lock( 0, 0, (void**)&verts, NULL );
	memcpy( verts, vertex, vertListSize );
	_wireCylinderVertexBuffer->Unlock();

	delete[] vertex;
}

void CollisionShapeRenderer::CreateWireCylinderClose( int slices, DWORD color )
{
	int i;
	int vertexNumber = 0;
	int vertexCount;
	float phiStep;
	LineVertex* vertex;

	phiStep = (3.141592f * 2.0f) / slices;

	vertexNumber = slices * 12;

	_wireCylinderCloseVertex = vertexNumber;

	vertex = new LineVertex[vertexNumber];

	int vertListSize = sizeof( LineVertex ) * vertexNumber;

	D3D9_DEVICE->CreateVertexBuffer( vertListSize, 0, D3DFVF_XYZ | D3DFVF_NORMAL,
									 D3DPOOL_MANAGED, &_wireCylinderCloseVertexBuffer, NULL );
	vertexCount = 0;

	for (i = 0; i < slices; i += 1)
	{
		vertex[vertexCount]._pos.x = cosf( phiStep*i ); 
		vertex[vertexCount]._pos.y = sinf( phiStep*i ); 
		vertex[vertexCount]._pos.z = 1.0f;
		vertex[vertexCount]._diffuse = color;
		vertexCount += 1;

		vertex[vertexCount]._pos.x = cosf( phiStep*i ); 
		vertex[vertexCount]._pos.y = sinf( phiStep*i ); 
		vertex[vertexCount]._pos.z = -1.0f;
		vertex[vertexCount]._diffuse = color;
		vertexCount += 1;

		vertex[vertexCount]._pos.x = cosf( phiStep*(i + 1) ); 
		vertex[vertexCount]._pos.y = sinf( phiStep*(i + 1) ); 
		vertex[vertexCount]._pos.z = 1.0f;
		vertex[vertexCount]._diffuse = color;
		vertexCount += 1;

		vertex[vertexCount]._pos.x = cosf( phiStep*(i + 1) ); 
		vertex[vertexCount]._pos.y = sinf( phiStep*(i + 1) ); 
		vertex[vertexCount]._pos.z = 1.0f;
		vertex[vertexCount]._diffuse = color;
		vertexCount += 1;

		vertex[vertexCount]._pos.x = cosf( phiStep*i ); 
		vertex[vertexCount]._pos.y = sinf( phiStep*i ); 
		vertex[vertexCount]._pos.z = -1.0f;
		vertex[vertexCount]._diffuse = color;
		vertexCount += 1;

		vertex[vertexCount]._pos.x = cosf( phiStep*(i + 1) ); 
		vertex[vertexCount]._pos.y = sinf( phiStep*(i + 1) ); 
		vertex[vertexCount]._pos.z = -1.0f;
		vertex[vertexCount]._diffuse = color;
		vertexCount += 1;


		vertex[vertexCount]._pos.x = 0.0f; 
		vertex[vertexCount]._pos.y = 0.0f; 
		vertex[vertexCount]._pos.z = 1.0f;
		vertex[vertexCount]._diffuse = color;
		vertexCount += 1;

		vertex[vertexCount]._pos.x = cosf( phiStep*i ); 
		vertex[vertexCount]._pos.y = sinf( phiStep*i ); 
		vertex[vertexCount]._pos.z = 1.0f;
		vertex[vertexCount]._diffuse = color;
		vertexCount += 1;

		vertex[vertexCount]._pos.x = cosf( phiStep*(i + 1) ); 
		vertex[vertexCount]._pos.y = sinf( phiStep*(i + 1) ); 
		vertex[vertexCount]._pos.z = 1.0f;
		vertex[vertexCount]._diffuse = color;
		vertexCount += 1;


		vertex[vertexCount]._pos.x = 0.0f; 
		vertex[vertexCount]._pos.y = 0.0f; 
		vertex[vertexCount]._pos.z = -1.0f;
		vertex[vertexCount]._diffuse = color;
		vertexCount += 1;

		vertex[vertexCount]._pos.x = cosf( phiStep*(i + 1) ); 
		vertex[vertexCount]._pos.y = sinf( phiStep*(i + 1) ); 
		vertex[vertexCount]._pos.z = -1.0f;
		vertex[vertexCount]._diffuse = color;
		vertexCount += 1;

		vertex[vertexCount]._pos.x = cosf( phiStep*i ); 
		vertex[vertexCount]._pos.y = sinf( phiStep*i ); 
		vertex[vertexCount]._pos.z = -1.0f;
		vertex[vertexCount]._diffuse = color;
		vertexCount += 1;

	}

	VOID *verts = NULL;

	_wireCylinderCloseVertexBuffer->Lock( 0, 0, (void**)&verts, NULL );
	memcpy( verts, vertex, vertListSize );
	_wireCylinderCloseVertexBuffer->Unlock();

	delete[] vertex;
}

void CollisionShapeRenderer::CreateWireSphere( int slices, int stacks, DWORD color )
{
	int i, j;
	int vertexNumber = 0;
	int vertexCount;
	float thetaStep;
	float phiStep;
	LineVertex* vertex;

	thetaStep = (3.141592f) / stacks;
	phiStep = (3.141592f * 2.0f) / slices;

	vertexNumber = slices*stacks * 2 + slices*(stacks - 1) * 2;

	_wireSphereVertexNumber = vertexNumber;

	vertex = new LineVertex[vertexNumber];

	int vertListSize = sizeof( LineVertex ) * vertexNumber;

	D3D9_DEVICE->CreateVertexBuffer( vertListSize, 0, D3DFVF_XYZ | D3DFVF_DIFFUSE,
									  D3DPOOL_MANAGED, &_wireSphereVertexBuffer, NULL );
	vertexCount = 0;

	for (i = 0; i < slices; i += 1)
	{
		for (j = 0; j < stacks; j += 1)
		{
			vertex[vertexCount]._pos.x = sinf( thetaStep*j )*cosf( phiStep*i );	
			vertex[vertexCount]._pos.y = sinf( thetaStep*j )*sinf( phiStep*i );	
			vertex[vertexCount]._pos.z = cosf( thetaStep*j );
			vertex[vertexCount]._diffuse = color;
			vertexCount += 1;

			vertex[vertexCount]._pos.x = sinf( thetaStep*(j + 1) )*cosf( phiStep*i );	
			vertex[vertexCount]._pos.y = sinf( thetaStep*(j + 1) )*sinf( phiStep*i );	
			vertex[vertexCount]._pos.z = cosf( thetaStep*(j + 1) );
			vertex[vertexCount]._diffuse = color;
			vertexCount += 1;
		}
	}

	for (j = 1; j < stacks; j += 1)
	{
		for (i = 0; i < slices; i += 1)
		{
			vertex[vertexCount]._pos.x = sinf( thetaStep*j )*cosf( phiStep*i );	
			vertex[vertexCount]._pos.y = sinf( thetaStep*j )*sinf( phiStep*i );	
			vertex[vertexCount]._pos.z = cosf( thetaStep*j );
			vertex[vertexCount]._diffuse = color;
			vertexCount += 1;

			vertex[vertexCount]._pos.x = sinf( thetaStep*(j) )*cosf( phiStep*(i + 1) );	
			vertex[vertexCount]._pos.y = sinf( thetaStep*j )*sinf( phiStep*(i + 1) );	
			vertex[vertexCount]._pos.z = cosf( thetaStep*j );
			vertex[vertexCount]._diffuse = color;
			vertexCount += 1;
		}
	}

	VOID *verts = NULL;

	_wireSphereVertexBuffer->Lock( 0, 0, (void**)&verts, NULL );


	memcpy( verts, vertex, vertListSize );
	_wireSphereVertexBuffer->Unlock();

	delete[] vertex;
}

void CollisionShapeRenderer::RenderWireRigidBody( btRigidBody *rigidBody, DWORD color )
{
	if (!rigidBody || !rigidBody->getCollisionShape() || !rigidBody->getMotionState())
	{
		return;
	}

	// change transform to matrix
	btTransform worldTransform;
	rigidBody->getMotionState()->getWorldTransform( worldTransform );

	D3DXMATRIX worldMatrix = btTransformToD3DXMATIRX( worldTransform );

	// push matrix in stack
	_matrixStack->Push();

	_matrixStack->MultMatrixLocal( &worldMatrix );
	RenderWireShape( rigidBody->getCollisionShape(), color );

	_matrixStack->Pop();
}


void CollisionShapeRenderer::RenderWireShape( const btCollisionShape* shape, DWORD color )
{
	//CreateWireSphere( 10, 10, D3DCOLOR_COLORVALUE( 1.0f, 1.0f, 1.0f, 1.0f ) );
	//CreateWireHalfSphere( 10, 10, D3DCOLOR_COLORVALUE( 0.0f, 0.0f, 0.0f, 1.0f ) );
	//CreateWireCylinder( 10, D3DCOLOR_COLORVALUE( 0.0f, 0.0f, 0.0f, 1.0f ) );
	//CreateWireCylinderClose( 10, D3DCOLOR_COLORVALUE( 0.2f, 0.2f, 0.2f, 1.0f ) );

	switch (shape->getShapeType())
	{
		case BOX_SHAPE_PROXYTYPE:
		{
			CreateWireBox();
			RenderWireBox( (btBoxShape*)shape, color );
			break;
		}

		case SPHERE_SHAPE_PROXYTYPE:
		{
			CreateWireSphere( 10, 10, D3DCOLOR_COLORVALUE( 1.0f, 1.0f, 1.0f, 1.0f ) );
			RenderWireSphere( (btSphereShape*)shape, color );
			break;
		}

		case CAPSULE_SHAPE_PROXYTYPE:
		{
			CreateWireHalfSphere( 10, 10, D3DCOLOR_COLORVALUE( 0.0f, 0.0f, 0.0f, 1.0f ) );
			CreateWireCylinder( 10, D3DCOLOR_COLORVALUE( 0.0f, 0.0f, 0.0f, 1.0f ) );
			RenderWireCapsule( (btCapsuleShape*)shape, color );
			break;
		}

		case CYLINDER_SHAPE_PROXYTYPE:
		{
			CreateWireCylinderClose( 10, D3DCOLOR_COLORVALUE( 0.2f, 0.2f, 0.2f, 1.0f ) );
			RenderWireCylinderClose( (btCylinderShape*)shape, color );
			break;
		}
	}
}

void CollisionShapeRenderer::RenderWireBox( const btBoxShape* shape, DWORD color )
{
	auto effect = _shader->GetEffect();	// shader effect

	btVector3 dim = shape->getHalfExtentsWithMargin();
	D3DXVECTOR3 demension = D3DXVECTOR3( dim.m_floats[0], dim.m_floats[1], dim.m_floats[2] );

	D3DXMATRIX WVP;
	D3DXMATRIX world;

	// push matrix in stack
	_matrixStack->Push();

	_matrixStack->ScaleLocal( demension.x, demension.y, demension.z );
	world = *(_matrixStack->GetTop());

	_matrixStack->Pop();

	// calculate matrices
	WVP = world * _viewProjection;
	effect->SetMatrix( "mWVP", &WVP );

	// color
	D3DXVECTOR4 colorVector;

	colorVector.w = (float)(color >> 24);
	colorVector.x = (float)((color << 8) >> 24);
	colorVector.y = (float)((color << 16) >> 24);
	colorVector.z = (float)((color << 24) >> 24);
	colorVector /= 255.0f;

	effect->SetVector( "Color", &colorVector );

	// start shader
	effect->Begin( NULL, 0 );
	effect->BeginPass( 0 );

	D3D9_DEVICE->SetFVF( LineVertex::GetFVF() );
	D3D9_DEVICE->SetStreamSource( 0, _wireBoxVertexBuffer, 0, sizeof( LineVertex ) );
	D3D9_DEVICE->SetIndices( _wireBoxIndexBuffer );
	D3D9_DEVICE->DrawIndexedPrimitive( D3DPT_LINELIST, 0, 0, 8, 0, 12 );

	effect->EndPass();
	effect->End();
}




void CollisionShapeRenderer::RenderWireSphere( const btSphereShape* pShape, DWORD color )
{
	float radius = pShape->getRadius();
	auto effect = _shader->GetEffect();

	D3DXMATRIX worldTM, worldViewProjectTM, invWorldTM;
	D3DXVECTOR4 vColor;

	_matrixStack->Push();
	_matrixStack->ScaleLocal( radius, radius, radius );
	worldTM = *(_matrixStack->GetTop());
	_matrixStack->Pop();
	worldViewProjectTM = worldTM * _viewProjection;

	vColor.w = (float)(color >> 24);
	vColor.x = (float)((color << 8) >> 24);
	vColor.y = (float)((color << 16) >> 24);
	vColor.z = (float)((color << 24) >> 24);
	vColor /= 255.0f;

	effect->SetVector( "Color", &vColor );
	effect->SetMatrix( "mWVP", &worldViewProjectTM );

	effect->Begin( NULL, 0 );
	effect->BeginPass( 0 );

	D3D9_DEVICE->SetFVF( LineVertex::GetFVF() );
	D3D9_DEVICE->SetStreamSource( 0, _wireSphereVertexBuffer, 0, sizeof( LineVertex ) );
	D3D9_DEVICE->DrawPrimitive( D3DPT_LINELIST, 0, _wireSphereVertexNumber / 2 );

	effect->EndPass();
	effect->End();
}


void CollisionShapeRenderer::RenderWireHalfSphere( float radius, DWORD color )
{
	auto effect = _shader->GetEffect();

	D3D9_DEVICE->SetRenderState( D3DRS_FILLMODE, D3DFILL_WIREFRAME );

	D3DXMATRIX worldViewProjectTM;
	D3DXMATRIX worldTM;
	D3DXVECTOR4 vColor;

	vColor.w = (float)(color >> 24);
	vColor.x = (float)((color << 8) >> 24);
	vColor.y = (float)((color << 16) >> 24);
	vColor.z = (float)((color << 24) >> 24);
	vColor /= 255.0f;
	effect->SetVector( "Color", &vColor );

	_matrixStack->Push();
	_matrixStack->ScaleLocal( radius, radius, radius );
	worldTM = *(_matrixStack->GetTop());
	_matrixStack->Pop();
	worldViewProjectTM = worldTM * _viewProjection;

	D3D9_DEVICE->SetFVF( LineVertex::GetFVF() );

	effect->SetMatrix( "mWVP", &worldViewProjectTM );

	effect->Begin( NULL, 0 );
	effect->BeginPass( 0 );

	D3D9_DEVICE->SetStreamSource( 0, _wireCylinderVertexBuffer, 0, sizeof( LineVertex ) );
	D3D9_DEVICE->DrawPrimitive( D3DPT_TRIANGLELIST, 0, _wireSphereVertex / 3 );

	effect->EndPass();
	effect->End();

	D3D9_DEVICE->SetRenderState( D3DRS_FILLMODE, D3DFILL_SOLID );
}

void CollisionShapeRenderer::RenderWireCylinderClose( const btCylinderShape* pShape, DWORD color )
{
	auto effect = _shader->GetEffect();

	btVector3 dim = pShape->getHalfExtentsWithMargin();
	float fHeight = dim.getZ();
	float fRadius = dim.getX();

	D3D9_DEVICE->SetRenderState( D3DRS_FILLMODE, D3DFILL_WIREFRAME );

	D3DXMATRIX worldViewProjectTM;
	D3DXMATRIX worldTM;
	D3DXVECTOR4 vColor;

	vColor.w = (float)(color >> 24);
	vColor.x = (float)((color << 8) >> 24);
	vColor.y = (float)((color << 16) >> 24);
	vColor.z = (float)((color << 24) >> 24);
	vColor /= 255.0f;
	effect->SetVector( "Color", &vColor );

	_matrixStack->Push();
	_matrixStack->ScaleLocal( fRadius, fRadius, fHeight );
	worldTM = *(_matrixStack->GetTop());
	_matrixStack->Pop();

	worldViewProjectTM = worldTM * _viewProjection;
	effect->SetMatrix( "mWVP", &worldViewProjectTM );

	D3D9_DEVICE->SetFVF( LineVertex::GetFVF() );

	effect->Begin( NULL, 0 );
	effect->BeginPass( 0 );

	D3D9_DEVICE->SetStreamSource( 0, _wireCylinderCloseVertexBuffer, 0, sizeof( LineVertex ) );
	D3D9_DEVICE->DrawPrimitive( D3DPT_TRIANGLELIST, 0, _wireCylinderCloseVertex / 3 );

	effect->EndPass();
	effect->End();

	D3D9_DEVICE->SetRenderState( D3DRS_FILLMODE, D3DFILL_SOLID );
}

void CollisionShapeRenderer::RenderWireCylinder( float fHeight, float fRadius, DWORD color )
{
	auto effect = _shader->GetEffect();

	D3D9_DEVICE->SetRenderState( D3DRS_FILLMODE, D3DFILL_WIREFRAME );

	D3DXMATRIX worldViewProjectTM;
	D3DXMATRIX worldTM;
	D3DXVECTOR4 vColor;

	vColor.w = (float)(color >> 24);
	vColor.x = (float)((color << 8) >> 24);
	vColor.y = (float)((color << 16) >> 24);
	vColor.z = (float)((color << 24) >> 24);
	vColor /= 255.0f;
	effect->SetVector( "Color", &vColor );

	_matrixStack->Push();
	_matrixStack->ScaleLocal( fRadius, fRadius, fHeight );
	worldTM = *(_matrixStack->GetTop());
	_matrixStack->Pop();

	worldViewProjectTM = worldTM * _viewProjection;
	effect->SetMatrix( "mWVP", &worldViewProjectTM );

	D3D9_DEVICE->SetFVF( LineVertex::GetFVF() );

	effect->Begin( NULL, 0 );
	effect->BeginPass( 0 );

	D3D9_DEVICE->SetStreamSource( 0, _wireCylinderVertexBuffer, 0, sizeof( LineVertex ) );
	D3D9_DEVICE->DrawPrimitive( D3DPT_TRIANGLELIST, 0, _wireCylinderVertex / 3 );

	effect->EndPass();
	effect->End();

	D3D9_DEVICE->SetRenderState( D3DRS_FILLMODE, D3DFILL_SOLID );
}

void CollisionShapeRenderer::RenderWireCapsule( const btCapsuleShape* pShape, DWORD color )
{
	float fHeight = pShape->getHalfHeight();
	float fRadius = pShape->getRadius();

	_matrixStack->Push();
	_matrixStack->TranslateLocal( 0.0f, 0.0f, fHeight );
	RenderWireHalfSphere( fRadius, color );
	_matrixStack->Pop();

	_matrixStack->Push();
	RenderWireCylinder( fHeight, fRadius, color );
	_matrixStack->Pop();

	_matrixStack->Push();
	_matrixStack->RotateAxisLocal( &D3DXVECTOR3( 0.0f, 1.0f, 0.0f ), D3DX_PI );
	_matrixStack->TranslateLocal( 0.0f, 0.0f, fHeight );
	RenderWireHalfSphere( fRadius, color );
	_matrixStack->Pop();
}


