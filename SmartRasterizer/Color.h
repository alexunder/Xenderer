/*
 * Copyright (C) 2015 2nd Foundation
 * All rights reserved
 */

#ifndef __H_SUCKING_COLOR
#define __H_SUCKING_COLOR

class Color
{
	public:
		float R, G, B, A;

		Color(float r = 1.0f, float g = 1.0f, float b = 1.0f, float a = 1.0f);

		unsigned int ToUInt32(bool isAlphaHead = true) const;

		Color operator + (const Color &c) const;
		Color operator - (const Color &c) const;
		Color operator * (float f) const;
};

#endif
