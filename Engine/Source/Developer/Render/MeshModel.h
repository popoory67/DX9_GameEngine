#pragma once

#include <d3dx9.h>
#include <string>

#include "Matrix.h"
#include "Shader.h"

#define DEFAULT_TEX "C:/Users/boseul/Documents/GitHub/NinetailEngine/Engine/Resource/texture.png"


class MeshModel;

using MeshModelPtr = shared_ptr<MeshModel>;

/**
 * this is abstraction class of mesh object classes that is the file extension of 'x', 'obj' and etc...
 * the class is basic on every mesh class.
 * the reason for using abstraction is to prevent to declare unnecessary data structure
 * (vector to manage modeling objects in the MeshManager).
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
	ShaderPtr GetShader() const { return _shader; }

	// get matrix instance.
	MatrixPtr GetMatrix() const { return _matrix; }

	// load mesh model
	virtual void LoadModel( const string& fileName ) = 0;

	// load texture file
	virtual void LoadTexture( const string& fileName ) = 0;

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

