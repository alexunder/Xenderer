/*
 * Copyright (C) 2015 2nd Foundation
 * All rights reserved
 */

#include "stdafx.h"
#include "Color.h"
#include "util.h"

using namespace tools;

Color::Color(float r, float g, float b, float a)
{
	R = r;
	G = g;
	B = b;
	A = a;
}

unsigned int Color::ToUInt32(bool isAlphaHead, bool isRGBOrder) const
{
	unsigned int r = (unsigned int)(R * 255.0f);
	unsigned int g = (unsigned int)(G * 255.0f);
	unsigned int b = (unsigned int)(B * 255.0f);
	unsigned int a = (unsigned int)(A * 255.0f);
    r = utils::CMID(r, 0, 255);
    g = utils::CMID(g, 0, 255);
    b = utils::CMID(b, 0, 255);
    a = utils::CMID(a, 0, 255);

    if (isAlphaHead)
    {
        if (isRGBOrder)
	        return (a << 24) | (r << 16) | (g << 8) | b;
        else
	        return (a << 24) | (b << 16) | (g << 8) | r;
    }
    else
    {
        if (isRGBOrder)
	        return (r << 24) | (g << 16) | (b << 8) | a;
        else
	        return (b << 24) | (g << 16) | (r << 8) | a;
    }
}

Color
Color::operator + (const Color &c) const
{
	return Color(R + c.R, G + c.G, B + c.B, A + c.A);
}

Color
Color::operator - (const Color &c) const
{
	return Color(R - c.R, G - c.G, B - c.B, A - c.A);
}

Color
Color::operator * (float f) const
{
	return Color(R * f, G * f, B * f, A * f);
}
