/*
* Copyright (C) 2015 2nd Foundation
* All rights reserved
*/

#include "MeshObjectModel.h"
#include "stdafx.h"

MeshObjectModel::MeshObjectModel(int num_mesh, int num_vertices,
						const int * vi, const int * ni, const int * uvi,
						const Point * point, const Normal * normal,
						const float *uv)
{
    m_num_triangles = num_mesh;
    m_num_vertices = num_vertices;

    if (vi)
    {
        m_VertexIndex = new int[3 * m_num_triangles];
        memcpy(m_VertexIndex, vi, 3 * m_num_triangles * sizeof(int));
    }
    else
        m_VertexIndex = NULL;

    if (ni)
    {
        m_NormalIndex = new int[3 * m_num_triangles];
        memcpy(m_NormalIndex, ni, 3 * m_num_triangles * sizeof(int));
    }
    else
        m_NormalIndex = NULL;

    if (uvi)
    {
        m_UVIndex = new int[3 * m_num_triangles];
        memcpy(m_UVIndex, uvi, 3 * m_num_triangles * sizeof(int));
    }
    else
        m_UVIndex = NULL;

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
}
