#pragma once
#include "MeshObject.h"

typedef vector< SHARED_PTR(MeshObject) >		MeshVector;

class MeshRenderer
{
public:
	MeshRenderer();
	~MeshRenderer();

	void						Init();
	void						Render();

	void						Release();

private:

	MeshVector*					_object;
};
