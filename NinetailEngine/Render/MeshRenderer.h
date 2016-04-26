#pragma once

//#include "RenderPCH.h"
#include "MeshObject.h"

typedef ::vector< SHARED_PTR(MeshObject) >		MeshVectorPtr;

class MeshRenderer
{
public:
	MeshRenderer();
	~MeshRenderer();

	void						Init();
	void						Render();

	void						Release();

private:

	MeshVectorPtr*				_object;
};
