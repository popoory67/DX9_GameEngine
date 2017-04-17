#include "AnimatedUnit.h"
#include "Resources.h"
#include "CollisionShapeRenderer.h"
#include "CollisionRenderUtil.h"
#include "Define.h"

bool animHit;

bool callbackAnim( btManifoldPoint& cp,
				   const btCollisionObjectWrapper* colObj0Wrap, int partId0, int index0,
				   const btCollisionObjectWrapper* colObj1Wrap, int partId1, int index1 )
{
	animHit = true;

	return false;
}


AnimatedUnit::AnimatedUnit( string modelName, string texName, const btVector3& position ) :
_modelName( modelName ),
_texName( texName ),
_position( position ),
_isClear( false )
{
	_rigid = new RigidBody();
}

AnimatedUnit::~AnimatedUnit()
{
	SAFE_DELETE( _rigid );
}

void AnimatedUnit::Start()
{
	CreateXAnimatedModel();

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
	gContactAddedCallback = callbackAnim;
}

void AnimatedUnit::Update()
{
	/*--- Collision detection ---*/
	if (gUnitClear)
	{
		gContactAddedCallback = callbackAnim;
	}

	/*--- Physics position ---*/
	btTransform trans;
	_rigid->GetRigidBody()->getMotionState()->getWorldTransform( trans );

	auto mat = CollisionRender::btTransformToD3DXMATIRX( trans );
	_modeling->GetMatrix()->SetWorld( mat );

	if (animHit && !_isClear)
	{
		_modeling->LoadTexture( TEX_BLUE );
		animHit = false;
		_isClear = true;
	}

	//--- Animation ---
	_modeling->SetAnimation( 3, 0 );
	_modeling->SetPose( 0.00001f );
}

// test
void AnimatedUnit::CreateXAnimatedModel()
{
	//--- Create 3D Model ---
	_modeling = XSkinnedMesh::Create( _modelName );
	_modeling->LoadTexture( _texName );
	_modeling->GetMatrix()->SetScale( 0.5f, 0.5f, 0.5f );
	_modeling->GetMatrix()->SetRotate( 0, 0, 89.5f );
	_modeling->GetMatrix()->SetPosition( 20, -17, 0 );
	MeshManager::Get()->AddMesh( _modeling );
}
