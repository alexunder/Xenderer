
#ifndef __H_VERTEX
#define __H_VERTEX

#include "Vector4f.h"
#include "Vector3f.h"

typedef struct _vertex {
    Vector4f point;
    float u;
    float v;
    Normal normal;
} Vertex;

typedef struct _simple_vertex
{
    float x;
    float y;
    float z;
    float w;
    float u;
    float v;
    float r;
    float g;
    float b;
    float rhw;
} vertex_t;

#endif
