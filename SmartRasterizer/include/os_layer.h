/*
 * Copyright (C) 2015 2nd Foundation
 * All rights reserved
 */

#ifndef __H_OS_LAYER
#define __H_OS_LAYER

#include "RendererCanvas.h"
#include "RenderDevice.h"


enum KeyPressState
{
    KEYPRESS_UP = 1,
    KEYPRESS_DOWN,
    KEYPRESS_LEFT,
    KEYPRESS_RIGHT,
    KEYPRESS_SPACE
};

class UIContext
{
public:
    UIContext(int width, int height)
    {
        mWidth = width;
        mHeight = height;
        mpCanvas = NULL;
        mDevice = NULL;
        mFB = NULL;
        mKeyPressState = 0;
        mIsGoingQuit = false;
        mPlatformWindow = NULL;
    }

    void Init(int argc, char *argv[]);
    void Prepare();
    void mainloop();
    void InvalidateArea();

    bool isQuit()
    {
        return mIsGoingQuit;
    }

    void setQuitFlag()
    {
        mIsGoingQuit = true;
    }

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

    int getKeyPressState()
    {
        return mKeyPressState;
    }
    void setKeyPressState(int state)
    {
        mKeyPressState = state;
    }
private:
    int mWidth;
    int mHeight;
    RendererCanvas * mpCanvas;
    RenderDevice * mDevice;
    unsigned int * mFB;
    int mKeyPressState;
    bool mIsGoingQuit;
    void * mPlatformWindow;
};

#endif
