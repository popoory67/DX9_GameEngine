#pragma once


class Graphics
{
public:

	~Graphics();

	static Graphics& Get();

	void Init(HWND hWnd);

	void RenderScene();

	void RenderState();

private:

	Graphics();

private:

	static Graphics* _instance;
};

