/*
 * Copyright (C) 2015 2nd Foundation
 * All rights reserved
 */

#include "stdafx.h"
#include <algorithm>
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

void RendererCanvas::SetPixel(int x, int y, const Color &color)
{
	if(x >= mWidth || y >= mHeight)
		return;

	mFrameBuffer[y * mWidth + x] = color.ToUInt32(true);
}

void RendererCanvas::SetPixel(float x, float y, const Color &color)
{
	if(x < 0.0f || y < 0.0f)
		return;

	SetPixel((int)x, (int)y, color);
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
                SetPixel(x, y, color);
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
                SetPixel(x, y, color);
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
                SetPixel(x, y, color);
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
                SetPixel(x, y, color);
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
                SetPixel(x, y, color);
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
                SetPixel(x, y, color);
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
                SetPixel(x, y, color);
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
                SetPixel(x, y, color);
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

#define ROUND(a) ((int)(a + 0.5))

void RendererCanvas::DrawLineWithDDA(const Color &color, int x1, int y1, int x2, int y2)
{
	int dx = x2 - x1;
	int dy = y2 - y1;

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

void RendererCanvas::RasterizeTriangle(const Color &color, int x0, int y0,
                                        int x1, int y1, int x2, int y2)
{
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
    //float inv2Area = 1.f / (2.f * area);

    // Check the triangle is backfacing.
    if (area <= 0.)
        return;

    // Loop over the bounding box of the pixels that the triangle possibly
    // covers.
    int py;
    int px;

    for (int py = yMin; py < yMax; ++py) {
        for (int px = xMin; px < xMax; ++px) {
            float e0 = edge_a_0 * px + edge_b_0 * py + edge_c_0;
            float e1 = edge_a_1 * px + edge_b_1 * py + edge_c_1;
            float e2 = edge_a_2 * px + edge_b_2 * py + edge_c_2;

            //Check the sample is outside the triangle
            if (e0 <= 0.f || e1 <= 0.f || e2 <= 0.f)
                continue;

            SetPixel(px, py, color);
        }
    }
}
