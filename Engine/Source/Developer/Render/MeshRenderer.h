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

	void Create(string fileName, const string& textureName = "", const string& shaderName = "");

private:

	MeshModelPtr _mesh;
};

