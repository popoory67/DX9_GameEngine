#pragma once

#include "Util.h"
#include "Component.h"
#include "MeshModel.h"


class MeshRenderer : public Component
{
public:
	MeshRenderer();
	~MeshRenderer();

	MeshModelPtr GetModel();

	MeshModelPtr Create(string fileName, const string& textureName = DEFAULT_TEX, const string& shaderName = DEFAULT_SHADER);

private:

	MeshModelPtr _mesh;
};

