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
#include "Vertex.h"

#include <vector>

using namespace std;

typedef struct _Triangle {
    Vertex p1;
    Vertex p2;
    Vertex p3;
} Triangle;

class MeshObjectModel
{
public:
	MeshObjectModel(int num_mesh, int num_vertise,
		const int * vi, const int * ni, const int * uvi,
		const Point * p, const Normal * n,
		const float *uv);

    ~MeshObjectModel() {
        if (m_pVertices != NULL)
            delete [] m_pVertices;

        if (m_VertexIndex != NULL)
            delete [] m_VertexIndex; 

        if (m_pNormals != NULL)
            delete [] m_pNormals; 

        if (m_NormalIndex != NULL)
            delete [] m_NormalIndex; 

        if (m_pUVs != NULL)
            delete [] m_pUVs; 

        if (m_UVIndex != NULL)
            delete [] m_UVIndex; 
    }

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
};

#endif
