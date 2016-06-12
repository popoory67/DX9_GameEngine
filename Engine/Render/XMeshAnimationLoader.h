#pragma once

struct Bone : public D3DXFRAME
{
	D3DXMATRIX	_combinedTransformationMatrix;
};

class XMeshAnimationLoader
{

public:
	XMeshAnimationLoader();
	~XMeshAnimationLoader();

private:

};

//D3DXLoadMeshHierarchyFromX(fileName.c_str(), D3DXMESH_SYSTEMMEM, D3D9_DEVICE, , , , );