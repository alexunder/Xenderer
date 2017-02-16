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

    void SetTexture(void *bits, int granularity, int w, int h);
    unsigned int TextureRead(float u, float v);
    void DrawFragment(MeshObjectModel * pObj);
    void DrawBox(float theta);
    void DrawPlane(int a, int b, int c, int d);
    void initCamera(float x, float y, float z);
private:
    void init(int width, int height);
    void DestroyBuffer();
    void DrawPrimitive(vertex_t *p1, vertex_t *p2, vertex_t *p3);
    void DrawPixel(int x, int y, const Color &c);
private:
    Transform mTransform;
	unsigned int mWidth;
	unsigned int mHeight;
	unsigned int * mFrameBuffer;
	unsigned int * mZBuffer;
	unsigned char * mTexture;
    int mTextureWidth;
    int mTextureHeight;
    float mMaxU;
    float mMaxV;
    int mGranularity;
    Color mBackgroundColor;
    Color mForegroundColor;
};

#endif
