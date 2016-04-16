#pragma once

#include "RenderPCH.h"
#include "CreateDeviceD3DX.h"
#include "MeshObject.h"


class MeshRenderer
{
public:
	MeshRenderer();
	~MeshRenderer();

	void						Init();
	void						Render();

	void						Release();

private:

	::vector< ::tr1::shared_ptr<MeshObject> >*		_object;
};
