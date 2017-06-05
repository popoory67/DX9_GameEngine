#include "RenderPCH.h"
#include "MeshRenderer.h"
#include "XMeshObject.h"
#include "ObjMeshObject.h"
//#include "FbxMeshObject.h"
#include "MeshManager.h"

MeshManager* MeshManager::_instance = nullptr;

MeshRenderer::MeshRenderer()
{

}

MeshRenderer::~MeshRenderer()
{

}


MeshModelPtr MeshRenderer::GetModel()
{
	return _mesh;
}

MeshModelPtr MeshRenderer::Create(string fileName, const string& textureName, const string& shaderName)
{
	string extension = Util::GetFileExtension(fileName);

	if (extension.empty())
	{
		assert(Util::ErrorMessage("it is wrong file extension."));
		return nullptr;
	}

	if (extension == "x" || extension == "X")
	{
		_mesh.reset(new XMeshObject());
	}

	else if (extension == "obj" || extension == "OBJ")
	{
		_mesh.reset(new ObjMeshObject());
	}

	else if (extension == "fbx" || extension == "FBX")
	{
		//_mesh.reset(new FbxMesh());
	}

	_mesh->LoadModel(fileName);
	_mesh->LoadTexture(textureName);
	_mesh->GetShader()->LoadShader(shaderName);

	MeshManager::Get().AddMesh(_mesh);

	return _mesh;
}