/*
 * Copyright (C) 2015 2nd Foundation
 * All rights reserved
 */

#ifndef __H_OS_LAYER
#define __H_OS_LAYER

#include "RendererCanvas.h"

class UIContext {
public:
    UIContext(int width, int height, RendererCanvas *canvas)
        : mpCanvas(canvas) { 
        mWidth = width;
        mHeight = height;
    }

    void Init(int argc, char *argv[]);
    void Prepare();

    int getWidth() {
        return mWidth;
    }

    int getHeight() {
        return mHeight;
    }

    RendererCanvas * getCanvas() {
        return mpCanvas;
    }
private:
    int mWidth;
    int mHeight;
    RendererCanvas * mpCanvas;
};

#endif
