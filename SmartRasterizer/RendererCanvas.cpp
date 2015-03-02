/*
 * Copyright (C) 2015 2nd Foundation
 * All rights reserved
 */

#include "stdafx.h"
#include <cstring>
#include <cmath>
#include "RendererCanvas.h"

/*
void RendererCanvas::SetFrameBuffer(unsigned int *frameBuffer,
                           unsigned int width, unsigned int height)
{
	mFrameBuffer = frameBuffer;
	mWidth  = width;
	mHeight = height;
}*/

RendererCanvas::~RendererCanvas()
{
	if(mFrameBuffer != NULL)
		free(mFrameBuffer);
}

void RendererCanvas::CreateFrameBuffer(unsigned int width, unsigned int height, const Color &color)
{
	mFrameBuffer = (unsigned int*)malloc(width*height*sizeof(unsigned int));
	//memset(mFrameBuffer, 0, sizeof(unsigned int) * mHeight * mWidth);

	unsigned int i;
	for(i = 0; i < width*height; i++)
	{
		mFrameBuffer[i] = color.ToUInt32();
	}

	mWidth  = width;
	mHeight = height;
}

unsigned int * RendererCanvas::getframeBuffer()
{
	return mFrameBuffer;
}

void RendererCanvas::SetPixel(unsigned int x, unsigned int y, const Color &color)
{
	if(x >= mWidth || y >= mHeight)
		return;

	mFrameBuffer[y * mWidth + x] = color.ToUInt32();
}

void RendererCanvas::SetPixel(float x, float y, const Color &color)
{
	if(x < 0.0f || y < 0.0f)
		return;

	SetPixel((unsigned int)x, (unsigned int)y, color);
}

void RendererCanvas::Clear()
{
	memset(mFrameBuffer, 0, sizeof(unsigned int) * mHeight * mWidth);
}

void RendererCanvas::DrawLine(const Color &color1, float x1, float y1,
                     const Color &color2, float x2, float y2)
{
	float xdiff = (x2 - x1);
	float ydiff = (y2 - y1);

	if(xdiff == 0.0f && ydiff == 0.0f) 
	{
		SetPixel(x1, y1, color1);
		return;
	}

	if(fabs(xdiff) > fabs(ydiff)) 
	{
		float xmin, xmax;

		// set xmin to the lower x value given
		// and xmax to the higher value
		if(x1 < x2) 
		{
			xmin = x1;
			xmax = x2;
		} 
		else 
		{
			xmin = x2;
			xmax = x1;
		}

		// draw line in terms of y slope
		float slope = ydiff / xdiff;
		for (float x = xmin; x <= xmax; x += 1.0f) 
		{
			float y = y1 + ((x - x1) * slope);
			Color color = color1 + ((color2 - color1) * ((x - x1) / xdiff));
			SetPixel(x, y, color);
		}
	} 
	else 
	{
		float ymin, ymax;

		// set ymin to the lower y value given
		// and ymax to the higher value
		if(y1 < y2) 
		{
			ymin = y1;
			ymax = y2;
		} 
		else 
		{
			ymin = y2;
			ymax = y1;
		}

		// draw line in terms of x slope
		float slope = xdiff / ydiff;
		for (float y = ymin; y <= ymax; y += 1.0f) 
		{
			float x = x1 + ((y - y1) * slope);
			Color color = color1 + ((color2 - color1) * ((y - y1) / ydiff));
			SetPixel(x, y, color);
		}
	}
}

void RendererCanvas::DrawLine(const Color &color, float x1, float y1, float x2, float y2)
{
	DrawLine(color, x1, y1, color, x2, y2);
}
	
void RendererCanvas::DrawLineWithBresenham(const Color &color, int x1, int y1, int x2, int y2)
{
	
}

#define ROUND(a) ((unsigned int)(a + 0.5))

void RendererCanvas::DrawLineWithDDA(const Color &color, unsigned int x1, unsigned int y1, unsigned int x2, unsigned int y2)
{
	unsigned int dx = x2 - x1;
	unsigned int dy = y2 - y1;

	unsigned int steps = 0;
	float xIncrement;
	float yIncrement;

	if (abs(dx) > abs(dy))
	{
		steps = abs(dx);
	}
	else
	{
		steps = abs(dy);
	}

	xIncrement = (float)dx / (float)steps;
	yIncrement = (float)dy / (float)steps;

	printf("xIncrement=%f\n", xIncrement);
	printf("yIncrement=%f\n", yIncrement);

	float x = x1;
	float y = y1;

	SetPixel(x, y, color);

	int i;

	for (i = 0; i < steps; i++)
	{
		x += xIncrement;
		y += yIncrement;
		SetPixel(ROUND(x), ROUND(y), color);
	}
}
