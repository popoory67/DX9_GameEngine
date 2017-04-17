/*
 * Parse .obj and .mtl file on C style
 */

#pragma once
#pragma warning (disable : 4996)

#include <vector>
#include <DirectXMath.h>
#include "DXVersion.h"

#if (CHECK_DX_VERSION == 11)
#include "D3D11Math.h"
#endif

#define LINE_BUFF_SIZE 4096


namespace ObjLoader
{
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT2 = DirectX::XMFLOAT2;

	struct ObjMaterialData
	{
		// Color (ka, kd, ks)
		XMFLOAT3 _ambient;
		XMFLOAT3 _diffuse;
		XMFLOAT3 _specular;

		ObjMaterialData()
		{
			_ambient = XMFLOAT3( 1, 1, 1 );
			_diffuse = XMFLOAT3( 1, 1, 1 );
			_specular = XMFLOAT3( 0.1f, 0.1f, 0.1f );
		}
	};

	struct ObjMaterial
	{
		// Material name.
		char _name[MAX_PATH];

		ObjMaterialData _materialData;

		// Transmission filter (tf)
		XMFLOAT3 _transFilter;

		// Transparency (also called d) (tr)
		float _transparency;

		// Specular power (ns)
		float _shininess;

		// Index of refraction (optical density) (Ni)
		float _refraction;

		// Illumination model (See remark at bottom of file) (illum)
		int _illumination;

		ObjMaterial() :
			_transparency( 1.0f ), // Fully opaque.
			_shininess( 32.0f ),
			_refraction( 1.0f ),
			_illumination( 2 ) // No default specified (?)
		{
			// Set material defaults (using mtl file specs).
			strncpy( _name, "default", MAX_PATH );

			_transFilter = XMFLOAT3( 1, 1, 1 );
		}
	};


	struct ObjMesh
	{

#if (CHECK_DX_VERSION == 9)
		using Float3 = D3DXVECTOR3;
		using Float2 = D3DXVECTOR2;
#else
		using Float3 = D3D11Math::Vector3;
		using Float2 = D3D11Math::Vector2;
#endif

		struct Face
		{
			int _firstVertex;
			int _firstTexCoord;
			int _firstNormal;

			int _verticesCount; // Number of vertices in this face.
		};

		struct Group
		{
			char _name[MAX_PATH];

			unsigned int _firstFace;
			unsigned int _numFaces;
		};

		vector< Float3 > _vertices;
		vector< Float3 > _normals;
		vector< Float2 > _texCoords;

		vector< Face > _faces;

		vector< int > _faceVertices;
		vector< int > _faceNormals;
		vector< int > _faceTexCoords;

		vector< Group > _groups;
		vector< Group > _matGroups; // defines a material to use, this material will continue to be used until another usemtl line(corresponding material is saved in.mtl file)

		vector< ObjMaterial* > _materials; // .mtl file data

		unsigned int _numTriangles; // differs from faces.size() if the mesh is not triangulated.

		Float3 _bbmin; // bounding box minimum values.
		Float3 _bbmax; // bounding box maximum values.

		char _mtlFileName[MAX_PATH];	// .mtl file name

		ObjMesh() : _numTriangles( 0 )
		{

		}

		~ObjMesh()
		{
			Clear();
		}

		void Clear()
		{
			_vertices.clear();
			_normals.clear();
			_texCoords.clear();
			_faces.clear();
			_matGroups.clear();
			_faceVertices.clear();
			_faceNormals.clear();

			_numTriangles = 0;

			for (UINT i = 0; i < _materials.size(); i++)
			{
				delete _materials[i];
			}

			_materials.clear();
		}

	};

	/**
	 * returns the index designating the end of the portion of the specified file name that defines the file path.
	 * @returns -1, if it fails
	 */
	int PathFromFileName( const string& fileName );

	// @returns the number of numbers in the string.
	int CountNumbers( const char* str );

	// identify that char is number.
	inline bool IsCharNumber( char ch )
	{
		return (ch >= '0' && ch <= '9');
	}

	// used by LoadMtlLib to read Ka, Kd, Ks, and Tf.
	bool ReadKx( const char* line, float* kx );

	/**
	 * loads an Obj file.
	 * @returns 1 on success, 0 on failure. Returns 2 if the obj.
	 */
	int LoadObj( const string& fileName, ObjMesh* outObjMesh );

	/**
	 * loads an .mtl file.
	 * this function is primarily used by LoadObj(), but is exposed here in case it's otherwise needed.
	 * @returns 0 on failure, 1 on success.
	 */
	int LoadMtl( const string& fileName, vector< ObjMaterial* >& materials );

	// identify face's v/t/n each other (in first face only once).
	bool InspectVertexDefinition( const char* firstVertex, bool& hasNormals, bool& hasTexCoords );

	// identify the number of face's vertex. (it is different every model)
	void InspectFaceLine( const char* line, int& faceVertexCount, bool inspectVertexComponents, bool& hasTexCoords, bool& hasNormals );
}