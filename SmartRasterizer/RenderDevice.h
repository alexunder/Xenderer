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

enum RenderState
{
    RENDERING_WIREFRAME = 1,
    RENDERING_TEXTURE   = 2,
    RENDERING_COLOR     = 4
};

class RenderDevice
{
public:
    RenderDevice(int width, int height);
    RenderDevice();

    ~RenderDevice()
    {
        DestroyBuffer();
    }

    void SetTexture(void *bits, int granularity, int w, int h);
    unsigned int TextureRead(float u, float v);
    void DrawFragment(MeshObjectModel * pObj);
    void DrawBox(float theta);
    void DrawPlane(int a, int b, int c, int d);
    void DrawLine(int x1, int y1, int x2, int y2);
    void initCamera(float x, float y, float z);
	void clear(int mode);
    unsigned int * getFB()
    {
        return mFrameBuffer;
    }
	void SetRenderState(RenderState state)
	{
		mRenderState = state;
	}
private:
    void init(int width, int height);
    void DestroyBuffer();
    void DrawPrimitive(vertex_t *p1, vertex_t *p2, vertex_t *p3);
    void DrawLineInner(int x1, int y1, int x2, int y2, const Color &color);
    void DrawPixel(int x, int y, const Color &c);
private:
    Transform mTransform;
	unsigned int mWidth;
	unsigned int mHeight;
	unsigned int * mFrameBuffer;
	float * mZBuffer;
	unsigned int * mTexture;
    int mTextureWidth;
    int mTextureHeight;
    float mMaxU;
    float mMaxV;
    int mGranularity;
    Color mBackgroundColor;
    Color mForegroundColor;
    int mRenderState;
};

#endif
