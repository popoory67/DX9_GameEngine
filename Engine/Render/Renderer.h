#pragma once

#include "MeshObject.h"

typedef SHARED_PTR(MeshObject)					MeshObjectPointer;
typedef vector< MeshObjectPointer >				MeshVector;

class Renderer
{
public:

	~Renderer();

	static Renderer&			Get();

	void						AddMesh(MeshObjectPointer mesh);

	void						Init();

	void						Render();

	void						Release();

private:

	Renderer();

private:

	static Renderer*			_instance;

	MeshVector*					_object;
};
