/*
 * Copyright (C) 2015 2nd Foundation
 * All rights reserved
 */

#include "RenderDevice.h"
#include "MeshObjectModel.h"

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

//For test only
void RenderDevice::DrawBox()
{

}

void RenderDevice::DrawPrimitive(Vertex *p1, Vertex *p2, Vertex *p3)
{

}

void RenderDevice::DrawPixel(int x, int y, const Color &c)
{

}
