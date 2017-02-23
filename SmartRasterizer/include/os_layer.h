/*
 * Copyright (C) 2015 2nd Foundation
 * All rights reserved
 */

#ifndef __H_OS_LAYER
#define __H_OS_LAYER

#include "RendererCanvas.h"
#include "RenderDevice.h"

class UIContext {
public:
    UIContext(int width, int height)
    {
        mWidth = width;
        mHeight = height;
        mpCanvas = NULL;
        mDevice = NULL;
        mFB = NULL;
    }

    void Init(int argc, char *argv[]);
    void Prepare();

    int getWidth()
    {
        return mWidth;
    }

    int getHeight()
    {
        return mHeight;
    }

    void SetCanvas(RendererCanvas * canvas)
    {
        mpCanvas = canvas;
        mFB = mpCanvas->getframeBuffer();
    }

    RendererCanvas * getCanvas() {
        return mpCanvas;
    }

    void SetRenderDevice(RenderDevice * device)
    {
        mDevice = device;
        mFB = mDevice->getFB();
    }

    RenderDevice * getRenderDevice()
    {
        return mDevice;
    }

    unsigned int * getFB()
    {
        return mFB;
    }
private:
    int mWidth;
    int mHeight;
    RendererCanvas * mpCanvas;
    RenderDevice * mDevice;
    unsigned int * mFB;
};

#endif
