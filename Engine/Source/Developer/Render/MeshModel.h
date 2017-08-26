#pragma once

#include <d3dx9.h>
#include <string>

#include "Component.h"
#include "D3D9Matrix.h"
#include "D3D9Shader.h"

#define DEFAULT_TEX "C:/Users/boseul/Documents/GitHub/NinetailEngine/Resource/texture.png"


class MeshModel;

/**
 * This is abstraction class of mesh object classes that is the file extension of 'x', 'obj' and etc...
 * The class is basic on every mesh class.
 * The reason for using abstraction is to prevent to declare unnecessary data structure
 * (vector to manage modeling objects in the MeshManager).
 */
class MeshModel : public Component
{
public:
	MeshModel();
	virtual ~MeshModel();

	/**
	 * The function to name this model.
	 * If you don't want to set object name, set the dafault name "Unknown".
	 */
	void			SetName( const string& objectName ) { _objectName = objectName; }

	// Get shader instance.
	ShaderPtr		GetShader() const		{ return _shader; }

	// Get matrix instance.
	D3D9MatrixPtr	GetMatrix() const		{ return _matrix; }

	// Load mesh model
	virtual void	LoadModel( const string& fileName ) = 0;

	// Load texture file
	virtual void	LoadTexture( const string& fileName = DEFAULT_TEX ) = 0;

	// A user must take shape the Render function.
	virtual void	Render() = 0;

protected:

	// Modeling name
	string			_objectName			= "Unknown";

	// Shader object
	ShaderPtr		_shader;

	// Mesh transform object
	D3D9MatrixPtr	_matrix;
};

