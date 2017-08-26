#pragma once

#include <DirectXMath.h>
#include <fbxsdk.h>


namespace FbxLoader
{
	using UVsetID = unordered_map<std::string, int>;
	using TextureSet = unordered_map<std::string, std::vector<std::string>>;

	struct FBX_MATRIAL_ELEMENT
	{
		enum MATERIAL_ELEMENT_TYPE
		{
			ELEMENT_NONE = 0,
			ELEMENT_COLOR,
			ELEMENT_TEXTURE,
			ELEMENT_BOTH,
			ELEMENT_MAX,
		};

		MATERIAL_ELEMENT_TYPE type;

		float r, g, b, a;

		TextureSet			textureSetArray;

		FBX_MATRIAL_ELEMENT()
		{
			textureSetArray.clear();
		}

		~FBX_MATRIAL_ELEMENT()
		{
			Release();
		}

		void Release()
		{
			for (TextureSet::iterator it = textureSetArray.begin(); it != textureSetArray.end(); ++it)
			{
				it->second.clear();
			}

			textureSetArray.clear();
		}
	};

	struct FBX_MATERIAL_NODE
	{

		enum eMATERIAL_TYPE
		{
			MATERIAL_LAMBERT = 0,
			MATERIAL_PHONG,
		};

		eMATERIAL_TYPE type;
		FBX_MATRIAL_ELEMENT ambient;
		FBX_MATRIAL_ELEMENT diffuse;
		FBX_MATRIAL_ELEMENT emmisive;
		FBX_MATRIAL_ELEMENT specular;

		float shininess;
		float TransparencyFactor;	
	};


	struct MESH_ELEMENTS
	{
		unsigned int	numPosition;
		unsigned int	numNormal;
		unsigned int	numUVSet;
	};


	struct FBX_MESH_NODE
	{
		std::string		name;
		std::string		parentName;

		MESH_ELEMENTS	elements;
		std::vector<FBX_MATERIAL_NODE> m_materialArray;
		UVsetID		uvsetID;

		std::vector<unsigned int>		indexArray;
		std::vector<FbxVector4>			m_positionArray;
		std::vector<FbxVector4>			m_normalArray;
		std::vector<FbxVector2>			m_texcoordArray;

		float	mat4x4[16];	// Matrix

		~FBX_MESH_NODE()
		{
			Release();
		}

		void Release()
		{
			uvsetID.clear();
			m_texcoordArray.clear();
			m_materialArray.clear();
			indexArray.clear();
			m_positionArray.clear();
			m_normalArray.clear();
		}
	};

	class CFBXLoader
	{
	public:
		enum eAXIS_SYSTEM
		{
			eAXIS_DIRECTX = 0,
			eAXIS_OPENGL,
		};

	protected:

		// FBX SDK
		FbxManager* mSdkManager;
		FbxScene*	mScene;
		FbxImporter* mImporter;
		FbxAnimLayer* mCurrentAnimLayer;

		std::vector<FBX_MESH_NODE>		m_meshNodeArray;

		void InitializeSdkObjects( FbxManager*& pManager, FbxScene*& pScene );
		void TriangulateRecursive( FbxNode* pNode );

		void SetupNode( FbxNode* pNode, std::string parentName );
		void Setup();

		void CopyVertexData( FbxMesh*	pMesh, FBX_MESH_NODE* meshNode );
		void CopyMatrialData( FbxSurfaceMaterial* mat, FBX_MATERIAL_NODE* destMat );

		void ComputeNodeMatrix( FbxNode* pNode, FBX_MESH_NODE* meshNode );

		void SetFbxColor( FBX_MATRIAL_ELEMENT& destColor, const FbxDouble3 srcColor );
		FbxDouble3 GetMaterialProperty(
			const FbxSurfaceMaterial * pMaterial,
			const char * pPropertyName,
			const char * pFactorPropertyName,
			FBX_MATRIAL_ELEMENT*			pElement );

		static void FBXMatrixToFloat16( FbxMatrix* src, float dest[16] )
		{
			unsigned int nn = 0;
			for (int i = 0; i < 4; i++)
			{
				for (int j = 0; j < 4; j++)
				{
					dest[nn] = static_cast<float>(src->Get( i, j ));
					nn++;
				}
			}
		}

	public:
		CFBXLoader();
		~CFBXLoader();

		void Release();

		HRESULT LoadFBX( const char* filename, const eAXIS_SYSTEM axis );
		FbxNode& GetRootNode();

		size_t GetNodesCount() { return m_meshNodeArray.size(); };

		FBX_MESH_NODE&	GetNode( const unsigned int id );
	};
}

