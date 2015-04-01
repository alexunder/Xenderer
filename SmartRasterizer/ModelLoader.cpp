/*
* Copyright (C) 2015 2nd Foundation
* All rights reserved
*/

#include "ModelLoader.h"
#include <stdio.h>
#include <stdlib.h>

#include <vector>

using namespace std;

bool loadObjModel(const char * path, ObjectModel & obj)
{
	std::vector<Vector3f> temp_vertices;
	std::vector<Vector2f> temp_uvs;
	std::vector<Vector3f> temp_normals;

	FILE * fp = fopen(path, "r");

	if (fp == NULL)
		return false;

	for (;;)
	{
		char lineHeader[128];
		// read the first word of the line
		int res = fscanf(fp, "%s", lineHeader);
		if (res == EOF)
			break; // EOF = End 

		if (strcmp(lineHeader, "v") == 0) //vertices case
		{
			float x;
			float y;
			float z;

			fscanf(fp, "%f %f %f", &x, &y, &z);
			temp_vertices.push_back(Vector3f(x, y, z));
		}
		else if (strcmp(lineHeader, "vn") == 0)//normals case
		{
			float x;
			float y;
			float z;

			fscanf(fp, "%f %f %f", &x, &y, &z);
			Vector3f vetice(x, y, z);

			temp_normals.push_back(vetice);
		}
		else if (strcmp(lineHeader, "vt") == 0)//texture case
		{
			float x;
			float y;
			fscanf(fp, "%f %f\n", &x, &y);
			y = -y; // Invert V coordinate since we will only use DDS texture, which are inverted. Remove if you want to use TGA or BMP loaders.
			temp_uvs.push_back(Vector2f(x, y));
		}
		else if (strcmp(lineHeader, "f") == 0)//faces case
		{
			unsigned int vertexIndex[3];
			unsigned int uvIndex[3];
			unsigned int normalIndex[3];
			
			int matches = fscanf(fp, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &vertexIndex[0], &uvIndex[0], &normalIndex[0], &vertexIndex[1], &uvIndex[1], &normalIndex[1], &vertexIndex[2], &uvIndex[2], &normalIndex[2]);
			if (matches != 9){
				printf("File can't be read by our simple parser :-( Try exporting with other options\n");
				return false;
			}

			TriangleMesh mesh;
			mesh.vertice[0] = temp_vertices[vertexIndex[0] - 1];
			mesh.vertice[1] = temp_vertices[vertexIndex[1] - 1];
			mesh.vertice[2] = temp_vertices[vertexIndex[2] - 1];

			mesh.normal[0] = temp_normals[normalIndex[0] - 1];
			mesh.normal[1] = temp_normals[normalIndex[1] - 1];
			mesh.normal[2] = temp_normals[normalIndex[2] - 1];

			mesh.uv[0] = temp_uvs[uvIndex[0] - 1];
			mesh.uv[1] = temp_uvs[uvIndex[1] - 1];
			mesh.uv[2] = temp_uvs[uvIndex[2] - 1];

			obj.AddMesh(mesh);
		}
		else
		{
			// Probably a comment, eat up the rest of the line
			char stupidBuffer[1000];
			fgets(stupidBuffer, 1000, fp);
		}
	}

	fclose(fp);

	return true;
}