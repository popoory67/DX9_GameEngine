#pragma once

#define FOV				( D3DX_PI / 4.0f )						// �þ߰�
#define ASPECT_RATIO	( SCREEN_WIDTH/(float)SCREEN_HEIGHT )	// ȭ���� ��Ⱦ��
#define NEAR_PLANE		1										// ���� ���
#define FAR_PLANE		500										// ���Ÿ� ���


class Camera
{
public:
	Camera();
	~Camera();

	virtual void	Init() = 0;

	virtual void	SetRotate( float x = 0, float y = 0, float z = 0 ) = 0;

	virtual void	SetPosition( float x = 0, float y = 0, float z = 0 ) = 0;

	virtual void	SetTransform() = 0;

	const int		GetID() const			{ return _id; }

	void			SetID( int id )			{ _id = id; }

private:

	int				_id		= 0;
};

