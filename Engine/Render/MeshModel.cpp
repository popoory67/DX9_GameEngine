#include "RenderPCH.h"
#include "MeshModel.h"


MeshModel::MeshModel() : _objectName("Unknown")
{
	_shader = Shader::Create();

	_matrix = Matrix::Create();
}


MeshModel::~MeshModel()
{

}

void MeshModel::SetObjectName( const string& objectName )
{
	_objectName = objectName;
}

