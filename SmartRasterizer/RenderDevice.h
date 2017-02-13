/*
 * Copyright (C) 2015 2nd Foundation
 * All rights reserved
 */

#ifndef __H_RENDER_DEVICE
#define __H_RENDER_DEVICE

#include "Transform.h"
#include "Color.h"
#include "Vertex.h"
#include "MeshObjectModel.h"

class RenderDevice
{
public:
    RenderDevice(int width, int height);
    ~RenderDevice();

    void DrawFragment(MeshObjectModel * pObj);
    void DrawBox();
private:
    void init(int width, int height);
    void DestroyBuffer();
    void DrawPrimitive(Vertex *p1, Vertex *p2, Vertex *p3);
    void DrawPixel(int x, int y, const Color &c);
private:
    Transform mTransform;
	unsigned int mWidth;
	unsigned int mHeight;
	unsigned int * mFrameBuffer;
	unsigned int * mZBuffer;
    Color mBackgroundColor;
    Color mForegroundColor;
};

#endif 
