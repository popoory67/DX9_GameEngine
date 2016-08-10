#include "RenderPCH.h"
#include "ObjLoader.h"


namespace ObjLoader
{
	int PathFromFileName(const string& fileName)
	{
		int ret = -2;
		int i = 0;

		LPCTSTR s = fileName.c_str();

		while (*s)
		{
			if (*s == TEXT('\\') || *s == TEXT('/'))
			{
				ret = i;
			}

			i++;
			s++;
		}

		return ret + 1;
	}

	int CountNumbers(const char* str)
	{
		const char* str2 = str;

		while (IsCharNumber(*str2))
		{
			str2++;
		}

		// the number of string
		return str2 - str;
	}

	bool IsCharNumber(char ch)
	{
		return (ch >= '0' && ch <= '9');
	}

	bool ReadKx(const char* line, float* kx)
	{
		// Specs say that y and z components are optional, and if they're not there then they're equal to x.
		if (0 == _stricmp("spectral", line + 3))
		{
			return false; // Not supported.
		}

		else if (0 == _stricmp("xyz", line + 3))
		{
			return false; // Not supported.
		}

		else if (3 != sscanf(line + 3, "%f %f %f", &kx[0], &kx[1], &kx[2]))
		{
			kx[1] = kx[2] = kx[0];
		}

		return true;
	}


	bool InspectVertexDefinition(const char* firstVertex, bool& hasNormals, bool& hasTexCoords)
	{
		hasNormals = false;
		hasTexCoords = false;

		const char* str = firstVertex;

		// skip the vertex position component.
		int len = CountNumbers(str);

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
		len = CountNumbers(str);

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
		len = CountNumbers(str);

		if (len > 0)
		{
			hasNormals = true;
		}

		return true;
	}

	void InspectFaceLine(const char* line, int& faceVertexCount, bool inspectVertexComponents, bool& hasTexCoords, bool& hasNormals)
	{
		int spaceCount = 0;

		// we determine the number of vertices by counting the spaces.
		for (const char* str = line + 1; *str != 0; str++)
		{
			if (*str != ' ')
			{
				continue;
			}

			if (!IsCharNumber(*(str + 1)))
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
				InspectVertexDefinition(str + 1, hasNormals, hasTexCoords);
			}
		}

		faceVertexCount = spaceCount;
	}

	int LoadMtl(const string& file_name, std::vector<ObjMaterial*>& materials)
	{
		CHAR buffer[LINE_BUFF_SIZE];

		FILE* pFile = _tfopen(file_name.c_str(), TEXT("r"));

		if (!pFile)
		{
			return 0;
		}

		ObjMaterial* pMat = NULL;

		while (!feof(pFile))
		{
			buffer[0] = 0;

			fgets(buffer, LINE_BUFF_SIZE, pFile);

			if (0 == strncmp("newmtl ", buffer, 7))
			{
				pMat = new ObjMaterial();
				materials.push_back(pMat);
				sscanf(buffer + 7, "%s", pMat->_name);
			}

			// skip anything until we find a newmtl statement.
			else if (pMat == NULL)
			{
				continue;
			}

			else if (0 == _strnicmp("ka ", buffer, 3))
			{
				ReadKx(buffer, pMat->_ambient);
			}

			else if (0 == _strnicmp("ks ", buffer, 3))
			{
				ReadKx(buffer, pMat->_specular);
			}

			else if (0 == _strnicmp("kd ", buffer, 3))
			{
				ReadKx(buffer, pMat->_diffuse);
			}

			else if (0 == _strnicmp("tf ", buffer, 3))
			{
				ReadKx(buffer, pMat->_transFilter);
			}

			else if (0 == _strnicmp("tr ", buffer, 3))
			{
				pMat->_transparency = (float)atof(buffer + 3);
			}

			else if (0 == _strnicmp("d ", buffer, 2))
			{
				pMat->_transparency = (float)atof(buffer + 2);
			}

			else if (0 == _strnicmp("ns ", buffer, 3))
			{
				pMat->_shininess = (float)atof(buffer + 3);
			}

			else if (0 == _strnicmp("Ni ", buffer, 3))
			{
				pMat->_refraction = (float)atof(buffer + 3);
			}

			else if (0 == _strnicmp("illum ", buffer, 6))
			{
				pMat->_illumination = atoi(buffer + 6);
			}

			else if (0 == _strnicmp("map_Ka ", buffer, 7))
			{
				sscanf(buffer + 7, "%s", pMat->_ambientName);
			}

			else if (0 == _strnicmp("map_Kd ", buffer, 7))
			{
				sscanf(buffer + 7, "%s", pMat->_diffuseName);
			}

			else if (0 == _strnicmp("map_Ks ", buffer, 7))
			{
				sscanf(buffer + 7, "%s", pMat->_specularName);
			}

			else if (0 == _strnicmp("map_Ns ", buffer, 7))
			{
				sscanf(buffer + 7, "%s", pMat->_shininessName);
			}

			else if (0 == _strnicmp("map_Tr ", buffer, 7))
			{
				sscanf(buffer + 7, "%s", pMat->_transparencyName);
			}

			else if (0 == _strnicmp("map_Disp ", buffer, 7))
			{
				sscanf(buffer + 9, "%s", pMat->_displacementName);
			}

			else if (0 == _strnicmp("map_Bump ", buffer, 7))
			{
				sscanf(buffer + 9, "%s", pMat->_bumpName);
			}

			else if (0 == _strnicmp("map_Refl ", buffer, 7))
			{
				sscanf(buffer + 9, "%s", pMat->_reflectionName);
			}

		}

		fclose(pFile);

		return 1;
	}

	int LoadObj(const string& file_name, ObjMesh* pOutObjMesh)
	{
		CHAR buffer[LINE_BUFF_SIZE];

		ObjMesh& obj = *pOutObjMesh;

		obj.Clear();

		FILE* pFile = _tfopen(file_name.c_str(), TEXT("r"));

		if (!pFile)
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

		pOutObjMesh->_mtlFileName[0] = 0;

		bool hasTexCoords = false, hasNormals = false;

		// We scan the file with two passes to determine the number of elements to Allocate.
		// Stupid obj file design.
		while (!feof(pFile))
		{
			buffer[0] = 0;
			fgets(buffer, LINE_BUFF_SIZE, pFile);

			if (0 == strncmp("v ", buffer, 2))
				numVertices++;

			else if (0 == strncmp("vn ", buffer, 3))
				numNormals++;

			else if (0 == strncmp("vt ", buffer, 3))
				numTexCoords++;

			else if (0 == strncmp("f ", buffer, 2))
			{
				numFaces++;

				int vCount = 0;

				InspectFaceLine(buffer, vCount, numFaces == 1, hasTexCoords, hasNormals);

				numFaceVertices += vCount;

				if (hasNormals)
					numFaceNormals += vCount;

				if (hasTexCoords)
					numFaceTexCoords += vCount;

				obj._numTriangles += vCount - 2;
			}

			else if (0 == strncmp("o ", buffer, 2))
				numObjects++;

			else if (0 == _strnicmp("usemtl ", buffer, 7))
				numMatGroups++;

			else if (0 == strncmp("g ", buffer, 2))
			{
				// The 'g' statement can include more than one group.
				for (const char* s = buffer; *s; s++)
				{
					if (*s == ' ')
						numGroups++;
				}
			}

			else if (0 == _strnicmp("mtllib ", buffer, 7))
				sscanf(buffer + 7, "%s", pOutObjMesh->_mtlFileName);
		}

		// failure
		if (numVertices == 0 || numFaces == 0)
		{
			fclose(pFile);
			return 0;
		}

		obj._vertices.resize(numVertices);
		obj._normals.resize(numNormals);
		obj._texCoords.resize(numTexCoords);
		obj._faces.resize(numFaces);

		obj._faceVertices.resize(numFaceVertices);
		obj._faceNormals.resize(numFaceNormals);
		obj._faceTexCoords.resize(numFaceTexCoords);

		obj._groups.resize(numGroups);
		obj._matGroups.resize(numMatGroups);

		rewind(pFile);

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

		while (!feof(pFile))
		{
			buffer[0] = '\0';

			fgets(buffer, LINE_BUFF_SIZE, pFile);

			if (0 == strncmp("v ", buffer, 2))
			{
				// vertex
				ObjMesh::Float3& v = obj._vertices[vertexCount++];
				sscanf(buffer + 1, "%f %f %f", &v.x, &v.y, &v.z);

				if (vertexCount == 1)
					obj._bbmin = obj._bbmax = v;

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

			else if (0 == strncmp("vn ", buffer, 3))
			{
				// normal
				sscanf(buffer + 2, "%f %f %f",
					&obj._normals[vNormalCount].x, &obj._normals[vNormalCount].y, &obj._normals[vNormalCount].z);

				vNormalCount++;
			}

			else if (0 == strncmp("vt ", buffer, 3))
			{
				// texture coordinate
				sscanf(buffer + 2, "%f %f",
					&obj._texCoords[vTexCoordCount].x, &obj._texCoords[vTexCoordCount].y);

				vTexCoordCount++;
			}

			else if (0 == strncmp("f ", buffer, 2))
			{
				// face
				ObjMesh::Face& face = obj._faces[faceCount];

				InspectFaceLine(buffer, face._verticesCount, false, hasTexCoords, hasNormals);

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
					v = atoi(s);

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
							t = atoi(s);

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

						n = atoi(s);

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

			else if (0 == _strnicmp("usemtl ", buffer, 7))
			{
				obj._matGroups[matCount]._firstFace = faceCount;

				obj._matGroups[matCount]._name[0] = 0;

				//strncpy( obj.matGroups[ mc ].name, buffer + 7, sizeof(obj.matGroups[0].name) );

				sscanf(buffer + 7, "%s", obj._matGroups[matCount]._name);

				obj._matGroups[matCount]._numFaces = 0;

				if (matCount > 0)
				{
					obj._matGroups[matCount - 1]._numFaces = faceCount - obj._matGroups[matCount - 1]._firstFace;
				}

				matCount++;
			}

			else if (0 == strncmp("g ", buffer, 2))
			{
				// The 'g' statement can include more than one group, in which case all that
				// follows belong to all groups on that line.
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
						sscanf(s + 1, "%s", obj._groups[groupCount + lastGroupCount]._name);
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

		fclose(pFile);

		// load mtl file.
		if (obj._mtlFileName == nullptr || obj._mtlFileName[0] == 0)
		{
			return 1;
		}

# ifndef UNICODE
		LPCTSTR mtlFileName = obj._mtlFileName;
# else
		TCHAR sMtlFileName[MAX_PATH];
		MultiByteToWideChar(CP_ACP, 0, obj.sMtlFileName, -1, sMtlFileName, MAX_PATH);
# endif

		if (0 >= LoadMtl(mtlFileName, obj._materials))
		{
			TCHAR libFile[MAX_PATH];

			INT n = PathFromFileName(file_name);

			if (n < 0)
			{
				return 2;
			}

			lstrcpyn(libFile, file_name.c_str(), n + 1);
			lstrcpyn(libFile + n, mtlFileName, MAX_PATH - n);

			if (0 >= LoadMtl(libFile, obj._materials))
			{
				return 2; // failed to load mtl file.
			}
		}

		return 1; // success
	}

}