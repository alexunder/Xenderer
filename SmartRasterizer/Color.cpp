/*
 * Copyright (C) 2015 2nd Foundation
 * All rights reserved
 */

#include "stdafx.h"
#include "Color.h"

Color::Color(float r, float g, float b, float a)
{
	R = r;
	G = g;
	B = b;
	A = a;
}

unsigned int Color::ToUInt32() const
{
	unsigned int r = (unsigned int)(R * 255.0f);
	unsigned int g = (unsigned int)(G * 255.0f);
	unsigned int b = (unsigned int)(B * 255.0f);
	unsigned int a = (unsigned int)(A * 255.0f);

	return (a << 24) | (r << 16) | (g << 8) | b;
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