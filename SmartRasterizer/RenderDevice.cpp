/*
 * Copyright (C) 2015 2nd Foundation
 * All rights reserved
 */

#include "RenderDevice.h"
#include "MeshObjectModel.h"
#include "util.h"
#include <stdlib.h>
#include <string.h>

using namespace tools;

RenderDevice::RenderDevice(int width, int height)
{
	mFrameBuffer = NULL;
	mZBuffer = NULL;
    init(width, height);
}

RenderDevice::RenderDevice()
{
    mWidth = 800;
    mHeight = 600;
    mFrameBuffer = NULL;
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
#ifdef __DEBUG
    cout<<"RenderDevice::init"<<endl;
    mTransform.DebugDump();
#endif
    mBackgroundColor.setColor(0xc0, 0xc0, 0xc0);
    mForegroundColor.setColor(0, 0, 0);
    mRenderState = RENDERING_WIREFRAME;
}

void RenderDevice::clear(int mode)
{
	int y;
	int x;
	int height = mHeight;
	for (y = 0; y < mHeight; y++)
	{
		//IUINT32 *dst = device->framebuffer[y];
		unsigned int cc = (height - 1 - y) * 230 / (height - 1);
		cc =(255 << 24) | (cc << 16) | (cc << 8) | cc;
		if (mode == 0)
			cc = mBackgroundColor.ToUInt32(true);
		for (x = mWidth; x > 0; x--)
			mFrameBuffer[y*mWidth + x] = cc;
	}

	for (y = 0; y < mHeight; y++)
	{
		for (x = mWidth; x > 0; x--)
			mZBuffer[y*mWidth + x] = 0.0f;
	}

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
    const Vector3f dir(-1, -0.5, 1);
    Matrix4f m = Matrix4f::rotation(dir, theta);
    Matrix4f w = m.transposed();
    mTransform.setWorld(w);
    mTransform.update();
#ifdef __DEBUG
    cout<<"RenderDevice::DrawBox"<<endl;
    mTransform.DebugDump();
#endif
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
#ifdef __DEBUG
	cout<<"DrawPrimitive, RenderState="<<mRenderState<<endl;
	cout<<"DrawPrimitive, before apply. p1, p2, p3, p4."<<endl;
	p1.print();
	p2.print();
	p3.print();
#endif
    Vector4f c1;
    Vector4f c2;
    Vector4f c3;

    mTransform.apply(p1, c1);
    mTransform.apply(p2, c2);
    mTransform.apply(p3, c3);
#ifdef __DEBUG
	cout<<"DrawPrimitive, before homo. c1, c2, c3, c4."<<endl;
	c1.print();
	c2.print();
	c3.print();
#endif
    if (mTransform.check_cvv(c1) != 0) return;
    if (mTransform.check_cvv(c2) != 0) return;
    if (mTransform.check_cvv(c3) != 0) return;

    mTransform.homogenize(c1, p1);
    mTransform.homogenize(c2, p2);
    mTransform.homogenize(c3, p3);
#ifdef __DEBUG
	cout<<"DrawPrimitive, after homo. p1, p2, p3, p4."<<endl;
	p1.print();
	p2.print();
	p3.print();
#endif

    if (mRenderState & (RENDERING_TEXTURE | RENDERING_COLOR))
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

            if (zrhw >= mZBuffer[py*mWidth + px])
            {
                mZBuffer[py*mWidth + px] = z;

                if (mRenderState & RENDERING_COLOR)
                {
                    float r = wt0 * v1->r + wt1 * v2->r + wt2 * v3->r;
                    float g = wt0 * v1->g + wt1 * v2->g + wt2 * v3->g;
                    float b = wt0 * v1->b + wt1 * v2->b + wt2 * v3->b;
					DrawPixel(px, py, Color(r, g, b));
                }

                if (mRenderState & RENDERING_TEXTURE)
                {
                    float u = wt0 * v1->u + wt1 * v2->u + wt2 * v3->u;
                    float v = wt0 * v1->v + wt1 * v2->v + wt2 * v3->v;
                    unsigned int cc = TextureRead(u, v);
                    unsigned char r = (cc & (0xff << 16)) >> 16;
                    unsigned char g = (cc & (0xff << 8 )) >> 8;
                    unsigned char b = cc & (0xff);
                    Color color;
                    color.setColor(r, g, b);
                    DrawPixel(px, py, color);
                }
            }
        }
    }

    if (mRenderState & RENDERING_WIREFRAME)
    {
        DrawLine(p1.x(), p1.y(), p2.x(), p2.y());
        DrawLine(p1.x(), p1.y(), p3.x(), p3.y());
        DrawLine(p3.x(), p3.y(), p2.x(), p2.y());
    }
}

void RenderDevice::DrawPixel(int x, int y, const Color &c)
{
    if(x >= mWidth || y >= mHeight)
        return;
#ifdef USE_GTK
    mFrameBuffer[ (mHeight - y) * mWidth + x] = c.ToUInt32(true, false);
#else
    mFrameBuffer[y * mWidth + x] = c.ToUInt32(true);
#endif
}

void RenderDevice::SetTexture(void *bits, int granularity, int w, int h)
{
    if (w > 1024 || h > 1024)
        return;

    mTexture = (unsigned int *)bits;
    mTextureWidth = w;
    mTextureHeight = h;
    mMaxU = (float)(w - 1);
    mMaxV = (float)(h - 1);
    mGranularity = granularity;
    mRenderState = RENDERING_TEXTURE;
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
    x = utils::CMID(x, 0, mTextureWidth - 1);
    y = utils::CMID(y, 0, mTextureHeight - 1);
    return mTexture[y*mTextureWidth + x];
}


void RenderDevice::initCamera(float x, float y, float z)
{
    Vector3f eye(x, y, z);
    Vector3f at(0.0, 0.0, 0.0);
    Vector3f up(0, 0, 1);
    mTransform.setCamera(Matrix4f::lookAt(eye, at, up));
    mTransform.update();
#ifdef __DEBUG
    cout<<"RenderDevice::initCamera."<<endl;
    mTransform.DebugDump();
#endif
}

void RenderDevice::DrawLine(int x1, int y1, int x2, int y2)
{
    DrawLineInner(x1, y1, x2, y2, mForegroundColor);
}

void RenderDevice::DrawLineInner(int x1, int y1, int x2, int y2, const Color &color)
{
    int dx = x2 - x1;
    int dy = y2 - y1;

    float slop = 0.0;
    float d;
    int x;
    int y;

    if (abs(dx) > abs(dy))
    {
        //Based on x
        slop = (float)dy / (float)dx;
        y = y1;

        if (dx >= 0 && dy >= 0)
        {
            d = slop;
            // The slop is positive
            for (x = x1; x <= x2; x++)
            {
                DrawPixel(x, y, color);
                if (d < 0.5)
                {
                    d += slop;
                }
                else
                {
                    y++;
                    d += slop - 1;
                }
            }
        }
        else if (dx >= 0 && dy < 0)
        {
            d = slop;
            // The slope is negative
            for (x = x1; x <= x2; x++)
            {
                DrawPixel(x, y, color);
                if (d > -0.5)
                {
                    d += slop;
                }
                else
                {
                    y--;
                    d += slop + 1;
                }
            }

        }
        else if (dx < 0 && dy >= 0)
        {
            d = -slop;
            // The slop is negative
            for (x = x1; x >= x2; x--)
            {
                DrawPixel(x, y, color);
                if (d < 0.5)
                {
                    d -= slop;
                }
                else
                {
                    y++;
                    //d += slop + 1;
                    d = d - slop -1;
                }
            }
        }
        else if (dx < 0 && dy < 0)
        {
            d = -slop;
            // The slop is positive
            for (x = x1; x >= x2; x--)
            {
                DrawPixel(x, y, color);
                if (d > -0.5)
                {
                    d -= slop;
                }
                else
                {
                    y--;
                    d = d - slop + 1;
                }
            }
        }
    }
    else
    {
        //based on y
        slop = (float)dx / (float)dy;
        x = x1;
        if (dy >= 0 && dx >= 0)
        {
            d = slop;
            // The slop is positive
            for (y = y1; y <= y2; y++)
            {
                DrawPixel(x, y, color);
                if (d < 0.5)
                {
                    d += slop;
                }
                else
                {
                    x++;
                    d += slop - 1;
                }
            }
        }
        else if (dy >= 0 && dx < 0)
        {
            d = slop;
            // The slope is negative
            for (y = y1; y <= y2; y++)
            {
                DrawPixel(x, y, color);
                if (d > -0.5)
                {
                    d += slop;
                }
                else
                {
                    x--;
                    d += slop + 1;
                }
            }

        }
        else if (dy < 0 && dx >= 0)
        {
            d = -slop;
            // The slop is negative
            for (y = y1; y >= y2; y--)
            {
                DrawPixel(x, y, color);
                if (d < 0.5)
                {
                    d -= slop;
                }
                else
                {
                    x++;
                    //d += slop + 1;
                    d = d - slop -1;
                }
            }
        }
        else if (dy < 0 && dx < 0)
        {
            d = -slop;
            // The slop is positive
            for (y = y1; y >= y2; y--)
            {
                DrawPixel(x, y, color);
                if (d > -0.5)
                {
                    d -= slop;
                }
                else
                {
                    x--;
                    d = d - slop + 1;
                }
            }
        }
    }
}
