#pragma once

#include "Util.h"
#include "Component.h"
#include "MeshModel.h"


class MeshRenderer : public Component
{
public:
	MeshRenderer();
	~MeshRenderer();

	MeshModel*	Create(string fileName, const string& textureName = DEFAULT_TEX, const string& shaderName = DEFAULT_SHADER);

	MeshModel*	GetModel();

private:

	MeshModel*	_mesh;
};

