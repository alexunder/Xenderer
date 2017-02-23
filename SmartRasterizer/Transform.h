/*
 * Copyright (C) 2015 2nd Foundation
 * All rights reserved
 */

#ifndef __H_TRANSFORM
#define __H_TRANSFORM

#include "Matrix4f.h"
#include "Vector4f.h"

class Transform
{
public:
    Transform(int w, int h);
    Transform()
    {
    }

    void init(int width, int height);
    void setWorld(Matrix4f &w)
    {
        mWorld = w;
    }
    void setCamera(Matrix4f c)
    {
        mCam = c;
    }
    void update();
    void apply(Vector4f &x, Vector4f &y);
    int check_cvv(Vector4f &v);
    void homogenize(Vector4f &x, Vector4f &y);
    void DebugDump();
private:
    Matrix4f mWorld;
    Matrix4f mCam;
    Matrix4f mProj;
    Matrix4f mFinal;
    float mWidth;
    float mHeight;
};

#endif
