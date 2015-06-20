/*
* Copyright (C) 2015 2nd Foundation
* All rights reserved
*/

#ifndef __H_OBJECT
#define __H_OBJECT

#include "Vector3f.h"
#include "Vector2f.h"
#include "Vector4f.h"
#include "Matrix4f.h"

#include <vector>

using namespace std;

class MeshObjectModel
{
public:
	MeshObjectModel(Vector3f wc, int num_mesh, int num_vertise,
		const int * vi, const int * ni, const int * uvi,
		const Point * p, const Normal * n,
		const float *uv);

	void SetWorldPosition(float x, float y, float z);
	void Transform(Matrix4f mt);
private:
	int m_num_triangles;
	int m_num_vertices;
	
	Point  * m_pVertices;
	int * m_VertexIndex;

	Normal * m_pNormals;
	int * m_NormalIndex;

	float  * m_pUVs;
	int * m_UVIndex;

	Vector3f worldPosition;
};

#endif