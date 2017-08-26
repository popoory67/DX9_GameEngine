#pragma once

#define SCREEN_WINDOW		false
#define SCREEN_FULL			true

// Window screen : false , Full screen : true
#define SCREEN_MODE			SCREEN_WINDOW

#define SCREEN_WIDTH		1280
#define SCREEN_HEIGHT		720


class D3DXRenderer
{
public:
	D3DXRenderer();
	virtual ~D3DXRenderer();

	virtual void			Init(HWND hWnd)		= 0;

	virtual void			RenderScene()		= 0;

	virtual void			RenderState()		= 0;
};

