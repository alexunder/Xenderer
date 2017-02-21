/*
 * Copyright (C) 2015 2nd Foundation
 * All rights reserved
 */

#include "RenderDevice.h"
#include "MeshObjectModel.h"
#include <stdlib.h>
#include <string.h>

int CMID(int x, int min, int max)
{ 
    return (x < min)? min : ((x > max)? max : x);
}

RenderDevice::RenderDevice(int width, int height)
{
    init(width, height);
}

RenderDevice::RenderDevice()
{
    mWidth = 800;
    mHeight = 600;
    mFrameBuffer = NULL;;
    mZBuffer = NULL;;
    mTexture = NULL;
    mTextureWidth = 2;
    mTextureHeight = 2;
    mMaxU = 1.0;
    mMaxV = 1.0;
    mGranularity = 32;
    mRenderState = 0;
}

void RenderDevice::init(int width, int height)
{
    DestroyBuffer();
    int BufferSize = width*height*4;
    mFrameBuffer = (unsigned int *)malloc(BufferSize);
    memset(mFrameBuffer, 0, BufferSize);
    mZBuffer = (float *)malloc(width*height*sizeof(float));
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
    mRenderState = RenderState::RENDERING_WIREFRAME;
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
    p1.u = 0, p1.v = 0, p2.u = 0, p2.v = 1;
    p3.u = 1, p3.v = 1, p4.u = 1, p4.v = 0;
    DrawPrimitive(&p1, &p2, &p3);
    DrawPrimitive(&p3, &p4, &p1);
}

void RenderDevice::DrawPrimitive(vertex_t *v1, vertex_t *v2, vertex_t *v3)
{
    Vector4f p1(v1->x, v1->y, v1->z, v1->w);
    Vector4f p2(v2->x, v2->y, v2->z, v2->w);
    Vector4f p3(v3->x, v3->y, v3->z, v3->w);

    Vector4f c1;
    Vector4f c2;
    Vector4f c3;

    mTransform.apply(p1, c1);
    mTransform.apply(p2, c2);
    mTransform.apply(p3, c3);

    if (mTransform.check_cvv(c1) != 0) return;
    if (mTransform.check_cvv(c2) != 0) return;
    if (mTransform.check_cvv(c3) != 0) return;

    mTransform.homogenize(c1, p1);
    mTransform.homogenize(c2, p2);
    mTransform.homogenize(c3, p3);

    if (mRenderState & (RenderState::RENDERING_TEXTURE |
                        RenderState::RENDERING_COLOR))
    {
        int x0 = p1.x();
        int x1 = p2.x();
        int x2 = p3.x();
        int y0 = p1.y();
        int y1 = p2.y();
        int y2 = p3.y();

        //Firstly build the bounding box
        int xMin = std::min(x0, std::min(x1, x2));
        int xMax = std::max(x0, std::max(x1, x2));
        int yMin = std::min(y0, std::min(y1, y2));
        int yMax = std::max(y0, std::max(y1, y2));

        // Triangle setup.
        // Compute the edge equation coefficients.
        float edge_a_0 = -(y1 - y0);
        float edge_a_1 = -(y2 - y1);
        float edge_a_2 = -(y0 - y2);

        float edge_b_0 =   x1 - x0;
        float edge_b_1 =   x2 - x1;
        float edge_b_2 =   x0 - x2;

        float edge_c_0 = edge_a_0 * -x0 + edge_b_0 * -y0;
        float edge_c_1 = edge_a_1 * -x1 + edge_b_1 * -y1;
        float edge_c_2 = edge_a_2 * -x2 + edge_b_2 * -y2;

        // Triangle area and inverse area
        float area = 0.5f * ((x1 - x0) * (y2 - y0) - (y1 - y0) * (x2 - x0));
        float inv2Area = 1.f / (2.f * area);

        // Check the triangle is backfacing.
        if (area <= 0.)
            return;

        // Loop over the bounding box of the pixels that the triangle possibly
        // covers.
        int py;
        int px;
        for (int py = yMin; py < yMax; ++py)
        for (int px = xMin; px < xMax; ++px)
        {
            float e0 = edge_a_0 * px + edge_b_0 * py + edge_c_0;
            float e1 = edge_a_1 * px + edge_b_1 * py + edge_c_1;
            float e2 = edge_a_2 * px + edge_b_2 * py + edge_c_2;

            //Check the sample is outside the triangle
            if (e0 <= 0.f || e1 <= 0.f || e2 <= 0.f)
                continue;

            float wt0 = e1 * inv2Area;
            float wt1 = e2 * inv2Area;
            float wt2 = e0 * inv2Area;

            // Interpolate z
            float z = (wt0 * p1.z() + wt1 * p2.z() + wt2 * p3.z());
            float zrhw = 1.0f / z;

            if (zrhw >= mZbuffer[py*mWidth + px])
            {
                mZbuffer[py*mWidth + px] = z;

                if (mRenderState & RenderState::RENDERING_COLOR)
                {
                    float r = wt0 * v1->r + wt1 * v2->r + wt2 * v3->r;
                    float g = wt0 * v1->g + wt1 * v2->g + wt2 * v3->g;
                    float b = wt0 * v1->b + wt1 * v2->b + wt2 * v3->b;
                    int R = (int)(r * 255.0f);
                    int G = (int)(g * 255.0f);
                    int B = (int)(b * 255.0f);
                    R = CMID(R, 0, 255);
                    G = CMID(G, 0, 255);
                    B = CMID(B, 0, 255);
                    mFrameBuffer[py*mWidth + px] = (R << 16) | (G << 8) | (B);
                }

                if (mRenderState & RenderState::RENDERING_TEXTURE)
                {
                }
            }
        }
    }

    if (mRenderState & RenderState::RENDERING_WIREFRAME)
    {
    }
}

void RenderDevice::DrawPixel(int x, int y, const Color &c)
{
    if(x >= mWidth || y >= mHeight)
        return;

    mFrameBuffer[y * mWidth + x] = c.ToUInt32(true);
}

void RenderDevice::SetTexture(void *bits, int granularity, int w, int h)
{
    if (w > 1024 || h > 1024)
        return;

    unsigned char *ptr = (unsigned char*)bits;
    mTexture = ptr;
    mTextureWidth = w;
    mTextureHeight = h;
    mMaxU = (float)(w - 1);
    mMaxV = (float)(h - 1);
    mGranularity = granularity;
    mRenderState = RenderState::RENDERING_TEXTURE;
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


void RenderDevice::initCamera(float x, float y, float z)
{
    Vector3f eye(x, y, z);
    Vector3f at(0.0, 0.0, 0.0);
    Vector3f up(0, 0, 1);
    mTransform.setCamera(Matrix4f::lookAt(eye, at, up));
    mTransform.update();
}
