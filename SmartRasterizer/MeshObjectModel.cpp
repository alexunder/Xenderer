/*
* Copyright (C) 2015 2nd Foundation
* All rights reserved
*/

#include "MeshObjectModel.h"

Point Transfer_From_Matrix4f(Matrix4f mt, Point ori)
{
	Vector4f ret;
	Vector4f original = Vector4f(ori);
	ret = mt * original;
	return Point(ret.x, ret.y, ret.z);
}

MeshObjectModel::MeshObjectModel(Vector3f wc, int num_mesh, int num_vertices,
						const int * vi, const int * ni, const int * uvi,
						const Point * point, const Normal * normal,
						const float *uv)
{
    m_num_triangles = num_mesh;
    m_num_vertices = num_vertices;

    m_VertexIndex = new int[3 * m_num_triangles];
    memcpy(m_VertexIndex, vi, 3 * m_num_triangles * sizeof(int));

    m_NormalIndex = new int[3 * m_num_triangles];
    memcpy(m_NormalIndex, ni, 3 * m_num_triangles * sizeof(int));

    m_UVIndex = new int[3 * m_num_triangles];
    memcpy(m_UVIndex, uvi, 3 * m_num_triangles * sizeof(int));

    if (uv) {
        m_pUVs = new float[2 * m_num_vertices];
        memcpy(m_pUVs, uv, 2 * m_num_vertices * sizeof(float));
    }
    else 
        m_pUVs = NULL;

    m_pVertices = new Point[m_num_vertices];
    memcpy(m_pVertices, point, m_num_vertices * sizeof(Point));

    if (normal) {
        m_pNormals = new Normal[m_num_vertices];
        memcpy(m_pNormals, normal, m_num_vertices * sizeof(Normal));
    }
    else 
        m_pNormals = NULL;

    //Prepare world transition matrix
    worldPosition = wc;
    Matrix4f mt(1.0, 0.0, 0.0, 0.0,
                0.0, 1.0, 0.0, 0.0,
                0.0, 0.0, 1.0, 0.0,
                worldPosition[0], worldPosition[1], worldPosition[2], 1.0);
    // Transform mesh vertices to world space
    for (int i = 0; i < m_num_vertices; ++i)
        m_pVertices[i] = Transfer_From_Matrix4f(mt, point[i]);
}

void MeshObjectModel::SetWorldPosition(float x, float y, float z)
{
    worldPosition = Vector3f(x, y, z);
}

void MeshObjectModel::Transform(Matrix4f mt)
{
    int i;

    for (int i = 0; i < m_num_vertices; ++i)
        m_pVertices[i] = Transfer_From_Matrix4f(mt, m_pVertices[i]);
}
