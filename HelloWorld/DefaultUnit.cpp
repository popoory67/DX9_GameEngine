#include "DefaultUnit.h"
#include "Resources.h"
#include "CollisionShapeRenderer.h"
#include "CollisionRenderUtil.h"
#include "Define.h"

bool defaultHit;

bool callbackDefault( btManifoldPoint& cp,
			   const btCollisionObjectWrapper* colObj0Wrap, int partId0, int index0,
			   const btCollisionObjectWrapper* colObj1Wrap, int partId1, int index1 )
{
	defaultHit = true;

	return false;
}


DefaultUnit::DefaultUnit( string modelName, string texName, const btVector3& position, ModelType type ) :
_modelName( modelName ), 
_texName( texName ), 
_position( position ),
_type( type ),
_isClear( false )
{
	_rigid = new RigidBody();
}

DefaultUnit::~DefaultUnit()
{
	SAFE_DELETE( _rigid );
}

void DefaultUnit::Start()
{
	switch (_type)
	{
		case X_DEFAULT:
			CreateXDefaultModel();
			break;

		case OBJ_DEFAULT:
			CreateObjDefaultModel();
			break;

		default:
			break;
	}

	/*--- Collision ---*/
	// create collision shape
	btCollisionShape* objColShape = new btBoxShape( btVector3( 10, 15, 10 ) ); //new btSphereShape( 20 );
	_rigid->SetCollisionShape( objColShape );
	objColShape->calculateLocalInertia( 1, btVector3( 0, 0, 0 ) );

	// initialization position in collision
	btTransform trans;
	trans.setIdentity();
	trans.setOrigin( _position );

	// create rigidbody
	_rigid->CreateMotionState( trans );
	auto objRigidBodyCI = _rigid->CreateRigidbodyConstructionInfo( 1 );
	_rigid->CreateRigidBody( objRigidBodyCI );

	// add to wire frame renderer
	CollisionWireFrame* _wire = new CollisionWireFrame( _rigid->GetRigidBody() );
	CollisionShapeRenderer::Get()->AddWireFrame( _wire );

	///*--- Collision detection ---*/
	//gContactAddedCallback = callbackDefault;
}

void DefaultUnit::Update()
{
	/*--- Collision detection ---*/
	if (!gUnitClear)
	{
		gContactAddedCallback = callbackDefault;
	}

	/*--- Physics position ---*/
	btTransform trans;
	_rigid->GetRigidBody()->getMotionState()->getWorldTransform( trans );

	auto mat = CollisionRender::btTransformToD3DXMATIRX( trans );
	_modeling->GetMatrix()->SetWorld( mat );

	if (defaultHit && !_isClear)
	{
		_modeling->LoadTexture( TEX_BLUE );
		defaultHit = false;
		_isClear = true;
		gUnitClear = true;
	}
}

// test
void DefaultUnit::CreateXDefaultModel()
{
	/*--- Create 3D Model ---*/
	_modeling = XMeshObject::Create( _modelName );
	_modeling->LoadTexture( _texName );
	_modeling->GetMatrix()->SetScale( 0.1f, 0.1f, 0.1f );
	_modeling->GetMatrix()->SetPosition( 0, 0, 0 );
	MeshManager::Get()->AddMesh( _modeling );
}

void DefaultUnit::CreateObjDefaultModel()
{
	/*--- Create 3D Model ---*/
	_modeling = ObjMeshObject::Create( _modelName );
	_modeling->LoadTexture( _texName );
	_modeling->GetMatrix()->SetScale( 2, 2, 2 );
	_modeling->GetMatrix()->SetPosition( 0, 0, 0 );
	MeshManager::Get()->AddMesh( _modeling );
}