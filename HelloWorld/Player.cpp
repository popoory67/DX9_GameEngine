#include "Player.h"
#include "Resources.h"
#include "DynamicWorld.h"
#include "InputHeader.h"


Player::Player()
{
	_bullet = new Bullet();
}

Player::~Player()
{
	SAFE_DELETE( _bullet );
}

void Player::Update()
{
	// test
	DynamicWorld::Get()->GetDynamicWorld()->stepSimulation( 1 / 60.f, 10 );

	KeyInput();
}


void Player::KeyInput()
{
	auto cam = CameraManager::Get()->GetCamera( 0 );

	// Shooting
	if (KEY_INPUT.IsKeyDown( VK_SPACE ))
	{
		_bullet->CreateBullet();
		_bullet->SetDetectionFlag();

		KEY_INPUT.KeyUp( VK_SPACE );
	}

	// Camera move
	if (KEY_INPUT.IsKeyDown( VK_W ))
	{
		cam->MoveForward( SPEED );
		cam->SetTransform();
	}

	if (KEY_INPUT.IsKeyDown( VK_S ))
	{
		cam->MoveForward( -SPEED );
		cam->SetTransform();
	}

	if (KEY_INPUT.IsKeyDown( VK_D ))
	{
		//cam->MoveSideward( SPEED );
		cam->SetRotate( SPEED, 0, 0 );
		cam->SetTransform();
	}

	if (KEY_INPUT.IsKeyDown( VK_A ))
	{
		//cam->MoveSideward( -SPEED );
		cam->SetRotate( -SPEED, 0, 0 );
		cam->SetTransform();
	}
}