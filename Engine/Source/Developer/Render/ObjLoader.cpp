#include "RenderPCH.h"
#include "ObjLoader.h"

namespace ObjLoader
{
	int PathFromFileName( const string& fileName )
	{
		int ret = -2;
		int i = 0;

		LPCTSTR s = fileName.c_str();

		while (*s)
		{
			if (*s == TEXT( '\\' ) || *s == TEXT( '/' ))
			{
				ret = i;
			}

			i++;
			s++;
		}

		return ret + 1;
	}

	int CountNumbers( const char* str )
	{
		const char* str2 = str;

		while (IsCharNumber( *str2 ))
		{
			str2++;
		}

		// the number of string
		return str2 - str;
	}

	bool ReadKx( const char* line, XMFLOAT3 kx )
	{
		// Specs say that y and z components are optional, 
		// and if they're not there then they're equal to x.
		if (0 == _stricmp( "spectral", line + 3 ))
		{
			return false;
		}

		else if (0 == _stricmp( "xyz", line + 3 ))
		{
			return false;
		}

		return true;
	}


	bool InspectVertexDefinition( const char* firstVertex, bool& hasNormals, bool& hasTexCoords )
	{
		hasNormals = false;
		hasTexCoords = false;

		const char* str = firstVertex;

		// skip the vertex position component.
		int len = CountNumbers( str );

		if (len == 0)
		{
			return false;
		}
		str += len;

		if (*str != '/' || *(str + 1) == 0)
		{
			return true;
		}
		str++;

		// move on to check for tex coords info.
		len = CountNumbers( str );

		if (len > 0)
		{
			hasTexCoords = true;
			str += len;
		}

		if (*str != '/' || *(str + 1) == 0)
		{
			return true;
		}
		str++;

		// check for normal info.
		len = CountNumbers( str );

		if (len > 0)
		{
			hasNormals = true;
		}

		return true;
	}

	void InspectFaceLine( const char* line, int& faceVertexCount, bool inspectVertexComponents, bool& hasTexCoords, bool& hasNormals )
	{
		int spaceCount = 0;

		// we determine the number of vertices by counting the spaces.
		for (const char* str = line + 1; *str != 0; str++)
		{
			if (*str != ' ')
			{
				continue;
			}

			if (!IsCharNumber( *(str + 1) ))
			{
				continue;
			}

			spaceCount++;
			if (spaceCount != 1)
			{
				continue;
			}

			// this is the first space. Let's examine the vertex info that comes next to determine
			// which vertex components the face contains.
			if (inspectVertexComponents)
			{
				InspectVertexDefinition( str + 1, hasNormals, hasTexCoords );
			}
		}

		faceVertexCount = spaceCount;
	}

	int LoadMtl( const string& fileName, vector<ObjMaterial*>& materials )
	{
		CHAR buffer[LINE_BUFF_SIZE];

		FILE* file = _tfopen( fileName.c_str(), TEXT( "r" ) );

		if (!file)
		{
			return 0;
		}

		ObjMaterial* material = NULL;

		while (!feof( file ))
		{
			buffer[0] = 0;

			fgets( buffer, LINE_BUFF_SIZE, file );

			if (0 == strncmp( "newmtl ", buffer, 7 ))
			{
				material = new ObjMaterial();
				materials.push_back( material );
				sscanf( buffer + 7, "%s", material->_name );
			}

			// skip anything until we find a newmtl statement.
			else if (!material)
			{
				continue;
			}

			else if (0 == _strnicmp( "ka ", buffer, 3 ))
			{
				ReadKx( buffer, material->_materialData._ambient );
			}

			else if (0 == _strnicmp( "ks ", buffer, 3 ))
			{
				ReadKx( buffer, material->_materialData._specular );
			}

			else if (0 == _strnicmp( "kd ", buffer, 3 ))
			{
				ReadKx( buffer, material->_materialData._diffuse );
			}

			else if (0 == _strnicmp( "tf ", buffer, 3 ))
			{
				ReadKx( buffer, material->_transFilter );
			}

			else if (0 == _strnicmp( "tr ", buffer, 3 ))
			{
				material->_transparency = (float)atof( buffer + 3 );
			}

			else if (0 == _strnicmp( "d ", buffer, 2 ))
			{
				material->_transparency = (float)atof( buffer + 2 );
			}

			else if (0 == _strnicmp( "ns ", buffer, 3 ))
			{
				material->_shininess = (float)atof( buffer + 3 );
			}

			else if (0 == _strnicmp( "Ni ", buffer, 3 ))
			{
				material->_refraction = (float)atof( buffer + 3 );
			}

			else if (0 == _strnicmp( "illum ", buffer, 6 ))
			{
				material->_illumination = atoi( buffer + 6 );
			}
		}

		fclose( file );

		return 1;
	}

	int LoadObj( const string& fileName, ObjMesh* outObjMesh )
	{
		CHAR buffer[LINE_BUFF_SIZE];

		ObjMesh& obj = *outObjMesh;

		obj.Clear();

		FILE* file = fopen( fileName.c_str(), TEXT( "r" ) );
		if (!file)
		{
			return 0;
		}

		int numVertices = 0;
		int numNormals = 0;
		int numTexCoords = 0;
		int numFaces = 0;
		int numObjects = 0;
		int numGroups = 0;
		int numMatGroups = 0;
		int numFaceVertices = 0;
		int numFaceNormals = 0;
		int numFaceTexCoords = 0;

		outObjMesh->_mtlFileName[0] = 0;

		bool hasTexCoords = false, hasNormals = false;

		// We scan the file with two passes to determine the number of elements to Allocate.
		// Stupid obj file design.
		while (!feof( file ))
		{
			buffer[0] = 0;
			fgets( buffer, LINE_BUFF_SIZE, file );

			if (0 == strncmp( "v ", buffer, 2 ))
				numVertices++;

			else if (0 == strncmp( "vn ", buffer, 3 ))
				numNormals++;

			else if (0 == strncmp( "vt ", buffer, 3 ))
				numTexCoords++;

			else if (0 == strncmp( "f ", buffer, 2 ))
			{
				numFaces++;

				int vCount = 0;

				InspectFaceLine( buffer, vCount, numFaces == 1, hasTexCoords, hasNormals );

				numFaceVertices += vCount;

				if (hasNormals)
					numFaceNormals += vCount;

				if (hasTexCoords)
					numFaceTexCoords += vCount;

				obj._numTriangles += vCount - 2;
			}

			else if (0 == strncmp( "o ", buffer, 2 ))
				numObjects++;

			else if (0 == _strnicmp( "usemtl ", buffer, 7 ))
				numMatGroups++;

			else if (0 == strncmp( "g ", buffer, 2 ))
			{
				// The 'g' statement can include more than one group.
				for (const char* s = buffer; *s; s++)
				{
					if (*s == ' ')
						numGroups++;
				}
			}

			else if (0 == _strnicmp( "mtllib ", buffer, 7 ))
				sscanf( buffer + 7, "%s", outObjMesh->_mtlFileName );
		}

		// failure
		if (numVertices == 0 || numFaces == 0)
		{
			fclose( file );
			return 0;
		}

		obj._vertices.resize( numVertices );
		obj._normals.resize( numNormals );
		obj._texCoords.resize( numTexCoords );
		obj._faces.resize( numFaces );

		obj._faceVertices.resize( numFaceVertices );
		obj._faceNormals.resize( numFaceNormals );
		obj._faceTexCoords.resize( numFaceTexCoords );

		obj._groups.resize( numGroups );
		obj._matGroups.resize( numMatGroups );

		rewind( file );

		UINT vertexCount = 0;
		UINT vNormalCount = 0;
		UINT vTexCoordCount = 0;

		UINT faceCount = 0;
		UINT fVertexCount = 0;
		UINT fNormalCount = 0;
		UINT fTexCoordCount = 0;

		UINT matCount = 0; // material counter.
		UINT groupCount = 0; // group counter.
		UINT lastGroupCount = 0; // number of groups on last encountered 'g ' line.

		while (!feof( file ))
		{
			buffer[0] = '\0';

			fgets( buffer, LINE_BUFF_SIZE, file );

			if (0 == strncmp( "v ", buffer, 2 ))
			{
				// vertex
				ObjMesh::Float3& v = obj._vertices[vertexCount++];
				sscanf( buffer + 1, "%f %f %f", &v.x, &v.y, &v.z );

				if (vertexCount == 1)
				{
					obj._bbmin = obj._bbmax = v;
				}

				else
				{
					// x
					if (v.x < obj._bbmin.x)
						obj._bbmin.x = v.x;

					else if (v.x > obj._bbmax.x)
						obj._bbmax.x = v.x;

					// y
					if (v.y < obj._bbmin.y)
						obj._bbmin.y = v.y;

					else if (v.y > obj._bbmax.y)
						obj._bbmax.y = v.y;

					// z
					if (v.z < obj._bbmin.z)
						obj._bbmin.z = v.z;

					else if (v.z > obj._bbmax.z)
						obj._bbmax.z = v.z;
				}
			}

			else if (0 == strncmp( "vn ", buffer, 3 ))
			{
				// normal
				sscanf( buffer + 2, "%f %f %f",
						&obj._normals[vNormalCount].x, &obj._normals[vNormalCount].y, &obj._normals[vNormalCount].z );

				vNormalCount++;
			}

			else if (0 == strncmp( "vt ", buffer, 3 ))
			{
				// texture coordinate
				sscanf( buffer + 2, "%f %f",
						&obj._texCoords[vTexCoordCount].x, &obj._texCoords[vTexCoordCount].y );

				vTexCoordCount++;
			}

			else if (0 == strncmp( "f ", buffer, 2 ))
			{
				// face
				ObjMesh::Face& face = obj._faces[faceCount];

				InspectFaceLine( buffer, face._verticesCount, false, hasTexCoords, hasNormals );

				face._firstVertex = fVertexCount;
				face._firstNormal = hasNormals ? fNormalCount : -1;
				face._firstTexCoord = hasTexCoords ? fTexCoordCount : -1;

				const char* s = buffer;

				for (int i = 0; i < face._verticesCount; i++)
				{
					int v = -1, t = -1, n = -1;

					/* add Face vertices */

					// remove blank next to f
					while (*s != ' ')
					{
						s++;
					}
					s++;

					// change number character to int
					v = atoi( s );

					if (v < 0)
					{
						v = vertexCount + v + 1;
					}

					obj._faceVertices[fVertexCount] = v - 1; // This is to make the indices 0-based numbering
					fVertexCount++; // plus array position

					/* add Face texture coordinates */
					if (hasTexCoords || hasNormals)
					{

						// move pointer to next number
						while (*s != '/')
						{
							s++;
						}
						s++;

						if (hasTexCoords)
						{
							t = atoi( s );

							if (t < 0)
							{
								t = vTexCoordCount + t + 2;
							}

							obj._faceTexCoords[fTexCoordCount] = t - 1;

							fTexCoordCount++;
						}
					}

					/* add Face normal */
					if (hasNormals)
					{
						while (*s != '/')
						{
							s++;
						}
						s++;

						n = atoi( s );

						if (n < 0)
						{
							n = vNormalCount + n + 2;
						}

						obj._faceNormals[fNormalCount] = n - 1;
						fNormalCount++;
					}
				}

				faceCount++;
			}

			else if (0 == _strnicmp( "usemtl ", buffer, 7 ))
			{
				obj._matGroups[matCount]._firstFace = faceCount;

				obj._matGroups[matCount]._name[0] = 0;

				sscanf( buffer + 7, "%s", obj._matGroups[matCount]._name );

				obj._matGroups[matCount]._numFaces = 0;

				if (matCount > 0)
				{
					obj._matGroups[matCount - 1]._numFaces = faceCount - obj._matGroups[matCount - 1]._firstFace;
				}

				matCount++;
			}

			else if (0 == strncmp( "g ", buffer, 2 ))
			{
				if (groupCount > 0)
				{
					for (UINT j = lastGroupCount; j > 0; j--)
					{
						obj._groups[groupCount - j]._numFaces = faceCount - obj._groups[groupCount - j]._firstFace;
					}
				}

				lastGroupCount = 0;

				for (const char* s = buffer; *s; s++)
				{
					if (*s == ' ')
					{
						sscanf( s + 1, "%s", obj._groups[groupCount + lastGroupCount]._name );

						obj._groups[groupCount + lastGroupCount]._firstFace = faceCount;
						obj._groups[groupCount + lastGroupCount]._numFaces = 0;

						lastGroupCount++;
					}
				}
				groupCount += lastGroupCount;
			}
		}

		// calculate face count for last defined material.
		if (matCount > 0)
		{
			obj._matGroups[matCount - 1]._numFaces = faceCount - obj._matGroups[matCount - 1]._firstFace;
		}

		// calculate face count for groups defined in last 'g ' statement.
		if (groupCount > 0)
		{
			for (UINT j = lastGroupCount; j > 0; j--)
			{
				obj._groups[groupCount - j]._numFaces = faceCount - obj._groups[groupCount - j]._firstFace;
			}
		}

		fclose( file );

		// load mtl file.
		if (obj._mtlFileName == nullptr || obj._mtlFileName[0] == 0)
		{
			return 1;
		}

# ifndef UNICODE
		LPCTSTR mtlFileName = obj._mtlFileName;
# else
		TCHAR mtlFileName[MAX_PATH];
		MultiByteToWideChar(CP_ACP, 0, obj.sMtlFileName, -1, sMtlFileName, MAX_PATH);
# endif

		if (0 >= LoadMtl( mtlFileName, obj._materials ))
		{
			TCHAR libFile[MAX_PATH];

			INT n = PathFromFileName( fileName );

			if (n < 0)
			{
				return 2;
			}

			lstrcpyn( libFile, fileName.c_str(), n + 1 );
			lstrcpyn( libFile + n, mtlFileName, MAX_PATH - n );

			if (0 >= LoadMtl( libFile, obj._materials ))
			{
				return 2; // failed to load mtl file.
			}
		}

		return 1; // success
	}

}