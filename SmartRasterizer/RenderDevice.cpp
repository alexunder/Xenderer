/*
 * Copyright (C) 2015 2nd Foundation
 * All rights reserved
 */

#include "RenderDevice.h"
#include "MeshObjectModel.h"

int CMID(int x, int min, int max)
{ 
    return (x < min)? min : ((x > max)? max : x);
}

RenderDevice::RenderDevice(int width, int height)
{
    init(width, height);
}

void RenderDevice::init(int width, int height)
{
    DestroyBuffer();
    int BufferSize = width*height*4;
    mFrameBuffer = (unsigned int *)malloc(BufferSize);
    memset(mFrameBuffer, 0, BufferSize);
    mZBuffer = (unsigned int *)malloc(BufferSize);
    memset(mZBuffer, 0, BufferSize);
    mWidth = width;
    mHeight = height;
    mTextureWidth = 2;
    mTextureHeight = 2;
    mMaxU = 1.0;
    mMaxV = 1.0;
    mTransform.init(width, height);
    mBackgroundColor.setColor(0xff, 0xff, 0xff); 
    mForegroundColor.setColor(0, 0, 0);
}

void RenderDevice::DestroyBuffer()
{
    if (mFrameBuffer != NULL)
    {
        free(mFrameBuffer);
        mFrameBuffer = NULL;
    }

    if (mZBuffer != NULL)
    {
        free(mZBuffer);
        mZBuffer= NULL;
    }
}

void RenderDevice::DrawFragment(MeshObjectModel * pObj)
{

}

vertex_t mesh[8] = 
{
    { 1, -1,  1, 1 , 0, 0 , 1.0, 0.2, 0.2, 1},
    {-1, -1,  1, 1 , 0, 1 , 0.2, 1.0, 0.2, 1},
    {-1,  1,  1, 1 , 1, 1 , 0.2, 0.2, 1.0, 1},
    { 1,  1,  1, 1 , 1, 0 , 1.0, 0.2, 1.0, 1},
    { 1, -1, -1, 1 , 0, 0 , 1.0, 1.0, 0.2, 1},
    {-1, -1, -1, 1 , 0, 1 , 0.2, 1.0, 1.0, 1},
    {-1,  1, -1, 1 , 1, 1 , 1.0, 0.3, 0.3, 1},
    { 1,  1, -1, 1 , 1, 0 , 0.2, 1.0, 0.3, 1},
};


//For test only
void RenderDevice::DrawBox(float theta)
{
    const Vector3f dir(-1, 0.5, 1);
    Matrix4f m = Matrix4f::rotation(dir, theta);
    mTransform.setWorld(m);
    mTransform.update();
    DrawPlane(0, 1, 2, 3);
    DrawPlane(4, 5, 6, 7);
    DrawPlane(0, 4, 5, 1);
    DrawPlane(1, 5, 6, 2);
    DrawPlane(2, 6, 7, 3);
    DrawPlane(3, 7, 4, 0);

}

void RenderDevice::DrawPlane(int a, int b, int c, int d)
{
    vertex_t p1 = mesh[a];
    vertex_t p2 = mesh[b];
    vertex_t p3 = mesh[c];
    vertex_t p4 = mesh[d];
    p1.tc.u = 0, p1.tc.v = 0, p2.tc.u = 0, p2.tc.v = 1;
    p3.tc.u = 1, p3.tc.v = 1, p4.tc.u = 1, p4.tc.v = 0;
    DrawPrimitive(&p1, &p2, &p3);
    DrawPrimitive(&p3, &p4, &p1);
}

void RenderDevice::DrawPrimitive(vertex_t *p1, vertex_t *p2, vertex_t *p3)
{

}

void RenderDevice::DrawPixel(int x, int y, const Color &c)
{

}

void RenderDevice::SetTexture(void *bits, int granularity, int w, int h)
{
    unsigned char *ptr = (unsigned char*)bits;
    assert(w <= 1024 && h <= 1024);
    mTexture = ptr;
    mTextureWidth = w;
    mTextureHeight = h;
    mMaxU = (float)(w - 1);
    mMaxV = (float)(h - 1);
    mGranularity = granularity;
}

unsigned int RenderDevice::TextureRead(float u, float v)
{
    if (mTexture == NULL)
        return 0;
    int x;
    int y;
    u = u * mMaxU;
    v = v * mMaxV;
    x = (int)(u + 0.5f);
    y = (int)(v + 0.5f);
    x = CMID(x, 0, mTextureWidth - 1);
    y = CMID(y, 0, mTextureHeight - 1);
    return mTexture[y*mTextureWidth*mGranularity + x];
}
