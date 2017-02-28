/*
 * Copyright (C) 2015 2nd Foundation
 * All rights reserved
 */

#ifndef __H_SUCKING_COLOR
#define __H_SUCKING_COLOR

class Color
{
public:
    Color(float r = 1.0f, float g = 1.0f, float b = 1.0f, float a = 1.0f);

    void setColorf(float r, float g, float b)
    {
        R = r;
        G = g;
        B = b;
    }

    void setColor(unsigned char r, unsigned char g,  unsigned char b)
    {
        R = ((float)r / 255.0);
        G = ((float)g / 255.0);
        B = ((float)b / 255.0);
    }

    unsigned int ToUInt32(bool isAlphaHead = true, bool isRGBOrder = true) const;

    Color operator + (const Color &c) const;
    Color operator - (const Color &c) const;
    Color operator * (float f) const;
private:
    float R, G, B, A;
};

#endif
