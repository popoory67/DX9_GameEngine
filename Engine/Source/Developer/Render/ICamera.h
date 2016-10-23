#pragma once

#define FOV				( D3DX_PI / 4.0f )						// �þ߰�
#define ASPECT_RATIO	( SCREEN_WIDTH/(float)SCREEN_HEIGHT )	// ȭ���� ��Ⱦ��
#define NEAR_PLANE		1										// ���� ���
#define FAR_PLANE		100000									// ���Ÿ� ���


class ICamera
{
public:
	ICamera();
	~ICamera();

	virtual void Init() = 0;

	virtual void SetRotate() = 0;

	virtual void SetPosition( float x = 0, float y = 0, float z = 0 ) = 0;

	const int GetID() const { return _id; }

	void SetID( int id ) { _id = id; }

private:

	int _id = 0;
};
