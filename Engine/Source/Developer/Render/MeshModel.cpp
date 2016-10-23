#include "RenderPCH.h"
#include "MeshModel.h"


MeshModel::MeshModel() : _objectName("Unknown")
{

}


MeshModel::~MeshModel()
{

}

void MeshModel::SetObjectName( const string& objectName )
{
	_objectName = objectName;
}

