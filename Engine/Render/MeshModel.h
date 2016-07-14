#pragma once

#include "Matrix.h"
#include "Shader.h"

#define DEFAULT_TEX "C:/Users/boseul/Documents/GitHub/NinetailEngine/Engine/Resource/texture.png"


class MeshModel;

using MeshModelPtr = shared_ptr<MeshModel>;

/**
 * this is abstraction class of mesh object classes that is the file extension of 'x', 'obj' and etc...
 * the class is base on every mesh class.
 * the reason for using abstraction is to prevent to declare unnecessary data structure (vector to manage modeling objects in the MeshManager).
 */
class MeshModel
{
public:

	MeshModel();
	virtual ~MeshModel();

	/**
	 * the function to name this model.
	 * if you don't want to set object name, set the dafault name "Unknown".
	 */
	void SetObjectName( const string& objectName );

	// get shader instance.
	virtual ShaderPtr GetShader() const;

	// get matrix instance.
	virtual MatrixPtr GetMatrix() const;

	// user must take shape thr Render function.
	virtual void Render() = 0;

protected:

	// modeling name
	string _objectName;

	// shader object
	ShaderPtr _shader;

	// mesh transform object
	MatrixPtr _matrix;
};

