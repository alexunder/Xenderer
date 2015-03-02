/*
 * Copyright (C) 2015 2nd Foundation
 * All rights reserved
 */

#ifndef __H_RENDERER_CANVAS
#define __H_RENDERER_CANVAS

#include "Color.h"

class RendererCanvas
{
public:
	~RendererCanvas();
private:
	unsigned int * mFrameBuffer;
	unsigned int mWidth;
	unsigned int mHeight;

private:
	void SetPixel(unsigned int x, unsigned int y, const Color &color = Color());
	void SetPixel(float x, float y, const Color &color = Color());
public:
	//void SetFrameBuffer(unsigned int *frameBuffer, unsigned int width, unsigned int height);
	void CreateFrameBuffer(unsigned int width, unsigned int height, const Color &color = Color());
	unsigned int * getframeBuffer();
	void Clear();

	void DrawLine(const Color &color1, float x1, float y1, const Color &color2, float x2, float y2);
	void DrawLine(const Color &color, float x1, float y1, float x2, float y2);
	void DrawLineWithBresenham(const Color &color, int x1, int y1, int x2, int y2);
	//void DrawCircle()
	void DrawLineWithDDA(const Color &color, unsigned int x1, unsigned int y1, unsigned int x2, unsigned int y2);
};

#endif
