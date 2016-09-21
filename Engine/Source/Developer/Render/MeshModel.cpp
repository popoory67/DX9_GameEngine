#include "RenderPCH.h"
#include "MeshModel.h"


MeshModel::MeshModel() : _objectName("Unknown")
{
	_shader = D3D9Shader::Create();

	_matrix = D3D9Matrix::Create();
}


MeshModel::~MeshModel()
{

}

void MeshModel::SetObjectName( const string& objectName )
{
	_objectName = objectName;
}

