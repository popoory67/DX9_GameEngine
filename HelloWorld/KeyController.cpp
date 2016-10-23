#include "KeyController.h"
#include "D3DXHeader.h"

KeyController::KeyController() : _x(0), _y(0), _z(0)
{
}


KeyController::~KeyController()
{
}

void KeyController::KeyInput()
{
	if (KEY_INPUT.IsKeyDown( VK_UP ))
	{
		CameraManager::Get()->GetCamera( 0 )->SetPosition( 0, 5, 0 );
	}

	if (KEY_INPUT.IsKeyDown( VK_DOWN ))
	{
		CameraManager::Get()->GetCamera( 0 )->SetPosition( 0, -5, -0 );
	}

	if (KEY_INPUT.IsKeyDown( VK_RIGHT ))
	{
		CameraManager::Get()->GetCamera( 0 )->SetPosition( 5, 0, 0 );
	}

	if (KEY_INPUT.IsKeyDown( VK_LEFT ))
	{
		CameraManager::Get()->GetCamera( 0 )->SetPosition( -5, 0, 0 );
	}
}


void KeyController::KeyInput( XMeshPtr model )
{
	if (KEY_INPUT.IsKeyDown( VK_UP ))
	{
		_y += 3;
		model->GetMatrix()->SetPosition( 0, _y, 0 );
	}

	if (KEY_INPUT.IsKeyDown( VK_DOWN ))
	{
		_y -= 3;
		model->GetMatrix()->SetPosition( 0, _y, -0 );
	}

	if (KEY_INPUT.IsKeyDown( VK_RIGHT ))
	{
		_x += 13;
		model->GetMatrix()->SetPosition( _x , 0, 0 );
	}

	if (KEY_INPUT.IsKeyDown( VK_LEFT ))
	{
		_x -= 13;
		model->GetMatrix()->SetPosition( _x , 0, 0 );
	}
}