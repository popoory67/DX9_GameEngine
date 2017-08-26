#pragma once

#define FOV				( D3DX_PI / 4.0f )						// 시야각
#define ASPECT_RATIO	( SCREEN_WIDTH/(float)SCREEN_HEIGHT )	// 화면의 종횡비
#define NEAR_PLANE		1										// 근접 평면
#define FAR_PLANE		500										// 원거리 평면


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

