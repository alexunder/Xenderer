/*
 * Copyright (C) 2015 2nd Foundation
 * All rights reserved
 */

#include "Transform.h"

#define PI 3.1415926f

Transform::Transform(int w, int h)
{
    init(w, h);
}

void Transform::init(int width, int height)
{
    float aspect = (float)width / ((float)height);
    mWorld = Matrix4f::identity();
    mCam = Matrix4f::identity();
    mProj = Matrix4f::perspectiveProjection(PI*0.5, aspect, 1.0, 500.0f, true);

    mWidth  = (float)width;
    mHeight = (float)height;
    update();
}

void Transform::update()
{
    Matrix4f m;
    m = mWorld * mCam;
    mFinal = m * mProj;
}

void Transform::apply(Vector4f &x, Vector4f &y)
{
    y = mFinal * x;
}

int Transform::check_cvv(Vector4f &v)
{
    float w = v.w();
    int check = 0;
    if (v.z() < 0.0f) check |= 1;
    if (v.z() >  w)   check |= 2;
    if (v.x() < -w)   check |= 4;
    if (v.x() >  w)   check |= 8;
    if (v.y() < -w)   check |= 16;
    if (v.y() >  w)   check |= 32;
    return check;
}

void Transform::homogenize(Vector4f &x, Vector4f &y)
{
    float rhw = 1.0f / x.w();
    y.x() = (x.x() * rhw + 1.0f) * mWidth * 0.5f;
    y.y() = (1.0f - x.y() * rhw) * mHeight * 0.5f;
    y.z() = x.z() * rhw;
    y.w() = 1.0f;
}

void Transform::DebugDump()
{
    cout<<"Transform Information:"<<endl;
    count<<"Width="<<mWidth<<"Height="<<mHeight<<endl;
    cout<<"The World matrix is"<<endl;
}
