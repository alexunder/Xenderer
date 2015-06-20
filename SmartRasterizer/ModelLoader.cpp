/*
* Copyright (C) 2015 2nd Foundation
* All rights reserved
*/

#include "ModelLoader.h"
#include "MeshObjectModel.h"
#include <stdio.h>
#include <stdlib.h>

#include <vector>

using namespace std;

bool loadObjModel(const char * path, MeshObjectModel ** obj)
{
	FILE * fp = fopen(path, "r");

	vector<unsigned int> vertexIndices;
	vector<unsigned int> uvIndices;
	vector<unsigned int> normalIndices;

	vector<Point>  point_buffer;
	vector<Normal> normal_buffer;
	vector<Vector2f>  mv_buffer;

	int number_mesh = 0;

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
			point_buffer.push_back(Point(x ,y ,z));
		}
		else if (strcmp(lineHeader, "vn") == 0)//normals case
		{
			float x;
			float y;
			float z;

			fscanf(fp, "%f %f %f", &x, &y, &z);
			Vector3f vetice(x, y, z);
			normal_buffer.push_back(Normal(x, y, z));
		}
		else if (strcmp(lineHeader, "vt") == 0)//texture case
		{
			float x;
			float y;
			fscanf(fp, "%f %f\n", &x, &y);
			y = -y; // Invert V coordinate since we will only use DDS texture, which are inverted. Remove if you want to use TGA or BMP loaders.
			mv_buffer.push_back(Vector2f(x, y));
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
			number_mesh++;
			vertexIndices.push_back(vertexIndex[0]);
			vertexIndices.push_back(vertexIndex[1]);
			vertexIndices.push_back(vertexIndex[2]);
			uvIndices.push_back(uvIndex[0]);
			uvIndices.push_back(uvIndex[1]);
			uvIndices.push_back(uvIndex[2]);
			normalIndices.push_back(normalIndex[0]);
			normalIndices.push_back(normalIndex[1]);
			normalIndices.push_back(normalIndex[2]);
		}
		else
		{
			// Probably a comment, eat up the rest of the line
			char stupidBuffer[1000];
			fgets(stupidBuffer, 1000, fp);
		}
	}

	fclose(fp);

	vector<Point>    point_intermediate_buffer;
	vector<Normal>   normal_intermediate_buffer;
	vector<Vector2f> mv_intermediate_buffer;

	int number_vertices = point_buffer.size();

	int * vertex_index = new int[3 * number_mesh];
	memcpy(vertex_index, &vertexIndices[0], 3 * number_mesh * sizeof(int));

	int * normal_index = new int[3 * number_mesh];
	memcpy(normal_index, &normalIndices[0], 3 * number_mesh * sizeof(int));

	int * uv_index = new int[3 * number_mesh];
	memcpy(uv_index, &uvIndices[0], 3 * number_mesh * sizeof(int));

	/*
	need to fill contents in these buffers
	*/

	Point * vertexBuffer = new Point[point_buffer.size()];
	memcpy(vertexBuffer, &point_buffer[0], point_buffer.size() * sizeof(Point));

	Normal * normalBuffer = new Normal[normal_buffer.size()];
	memcpy(normalBuffer, &normal_buffer[0], point_buffer.size() * sizeof(Normal));

	float * uvBuffer = new float[mv_buffer.size() * 2];
	int i;

	for (i = 0; i < mv_buffer.size(); i++)
	{
		uvBuffer[i * 2] = mv_buffer[i].x;
		uvBuffer[i * 2 + 1] = mv_buffer[i].y;
	}

	int count = 0;
	
	Vector3f wordCoord(0.0, 0.0, 0.0);
	*obj = new MeshObjectModel(wordCoord, number_mesh, number_vertices,
		vertex_index, normal_index, uv_index, 
		vertexBuffer, normalBuffer, uvBuffer);

	return true;
}