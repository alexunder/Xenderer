
#ifndef __H_VERTEX
#define __H_VERTEX

#include "Vector4f.h"
#include "Vector3f.h"

typedef struct _vertex {
    Vec4f point;
    float u;
    float v;
    Normal normal;
} Vertex;

#endif
