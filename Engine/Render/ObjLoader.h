#pragma once

#pragma warning (disable : 4996)

#define LINE_BUFF_SIZE 4096


struct ObjMaterial
{
	// Material name.
	char _name[MAX_PATH]; 

	// Color (ka, kd, ks)
	float _ambient[3];
	float _diffuse[3];
	float _specular[3];

	// Transmission filter (tf)
	float _transFilter[3];

	// Transparency (also called d) (tr)
	float _transparency;

	// Specular power (ns)
	float _shininess;

	// Index of refraction (optical density) (Ni)
	float _refraction;

	// Illumination model (See remark at bottom of file) (illum)
	int _illumination;

	// Map file names
	char _ambientName[MAX_PATH]; // Ambient texture file name (map_Ka)

	char _diffuseName[MAX_PATH]; // Diffuse texture file name (map_Kd)

	char _specularName[MAX_PATH]; // Specular color texture file name (map_Ks)

	char _shininessName[MAX_PATH]; // Specular power texture file name (map_Ns)

	char _transparencyName[MAX_PATH]; // Transparency texture file name (map_Tr)

	char _displacementName[MAX_PATH]; // Displacement map (map_Disp)

	char _bumpName[MAX_PATH]; // Bump map (map_Bump)

	char _reflectionName[MAX_PATH]; // Reflection map (map_Refl)

	ObjMaterial() :
		_transparency(1.0f), // Fully opaque.
		_shininess(32.0f),
		_refraction(1.0f),
		_illumination(2) // No default specified (?)
	{
		// Set material defaults (using mtl file specs).
		strncpy(_name, "default", MAX_PATH);

		for (int i = 0; i < 3; i++)
		{
			_ambient[i] = 0.2f;
			_diffuse[i] = 0.8f;
			//_specular[i] = 1.0f;
			_specular[i] = 0.f;

			_transFilter[i] = 1.0f;
		}

		_ambientName[0] = 0;
		_diffuseName[0] = 0;
		_specularName[0] = 0;
		_shininessName[0] = 0;
		_transparencyName[0] = 0;
		_displacementName[0] = 0;
		_bumpName[0] = 0;
		_reflectionName[0] = 0;
	}
};

struct ObjMesh
{

# ifdef __D3DX9_H__
	typedef D3DXVECTOR3 Float3;
	typedef D3DXVECTOR2 Float2;
# else
	struct Float3 { float x, y, z; };
	struct Float2 { float x, y; };
# endif

	struct Face
	{
		int _firstVertex; // Index into the mesh's vertex array - defines the first vertex of this face.
		int _firstTexCoord; // Like above, but can be -1 to specify face has no tex coords.
		int _firstNormal; // ~~

		int _verticesCount; // Number of vertices in this face.
	};

	struct Group
	{
		char _name[MAX_PATH];

		unsigned int _firstFace;
		unsigned int _numFaces;
	};

	std::vector< Float3 > _vertices;
	std::vector< Float3 > _normals;
	std::vector< Float2 > _texCoords;

	std::vector< Face > _faces;

	std::vector< int > _faceVertices;
	std::vector< int > _faceNormals;
	std::vector< int > _faceTexCoords;

	std::vector< Group > _groups;
	std::vector< Group > _matGroups; // Defines a material to use, this material will continue to be used until another usemtl line(corresponding material is saved in.mtl file)

	std::vector< ObjMaterial* > _materials; // .mtl file data

	unsigned int _numTriangles; // Differs from faces.size() if the mesh is not triangulated.

	Float3 _bbmin; // Bounding box minimum values.
	Float3 _bbmax; // Bounding box maximum values.

	char _mtlFileName[ MAX_PATH ];	// .mtl file name

	ObjMesh() : 
		_numTriangles(0)
	{ 

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


namespace ObjLoader
{
	// Returns the index designating the end of the portion of the specified file name
	// that defines the file path. Returns -1 if it fails.
	inline int PathFromFileName(LPCTSTR fileName);

	// Returns the number of numbers in the string.
	inline int CountNumbers(const char* str);

	inline bool IsCharNumber(char ch);

	// Utility function used internally by this module.
	// Used by LoadMtlLib to read Ka, Kd, Ks, and Tf.
	inline bool ReadKx(const char* line, float* kx);

	// Loads an Obj file. Returns 1 on success, 0 on failure. Returns 2 if the obj
	// file was loaded but the associated mtl file was not found.
	int LoadObj(LPCTSTR file_name, ObjMesh* pOutObjMesh);

	// Loads an .mtl file. This function is primarily used by LoadObj(), but is exposed here
	// in case it's otherwise needed.
	// Returns 0 on failure, 1 on success.
	int LoadMtl(LPCTSTR file_name, std::vector< ObjMaterial* >& materials);

	// face의 v/t/n이 각각 존재하는지 확인, 첫번째 face에서 한번만 확인
	bool InspectVertexDefinition(const char* firstVertex, bool& hasNormals, bool& hasTexCoords);

	// face의 vertex 개수가 몇개인지 확인 (모델마다 다르므로 확인해야함)
	void InspectFaceLine(const char* line, int& faceVertexCount, bool inspectVertexComponents, bool& hasTexCoords, bool& hasNormals);
}