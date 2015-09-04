/*
* Copyright (C) 2015 2nd Foundation
* All rights reserved
*
* The class for RGB operations
*/

#ifndef  __X_RGB_H
#define  __X_RGB_H

#include <iostream>

using namespace std;

class XRGB
{
public:
	XRGB()
	{
		m_r = m_g = m_b = 0;
	}

	XRGB(float red, float green, float blue);

	XRGB(const XRGB & original)
	{
		*this = original;
	}
	
	void setRed(float red)
	{
		m_r = red;
	}
	
	void setGreen(float green)
	{
		m_g = green;
	}
	
	void setBlue(float blue)
	{
		m_b = blue;
	}

	//These operators perform no clamping
	XRGB& operator=(const XRGB & right_op);
	XRGB& operator+=(const XRGB & right_op);
	XRGB& operator*=(const XRGB & right_op);
	XRGB& operator/=(const XRGB & right_op);
	XRGB& operator*=(float right_op);
	XRGB& operator/=(float right_op);

	XRGB operator+() const
	{
		return *this;
	}
	
	XRGB operator-() const
	{
		return XRGB(-m_r, -m_g, -m_b);
	}

	float r() const { return m_r; }
	float g() const { return m_g; }
	float b() const { return m_b; }

	void clamp();

	friend ostream& operator<<(ostream & out, const XRGB & the_rgb);
	friend XRGB operator*(const XRGB& c, float f);
	friend XRGB operator*(float f, const XRGB& c); 
	friend XRGB operator/(const XRGB& c, float f);
	friend XRGB operator*(const XRGB& c1, const XRGB& c2);
	friend XRGB operator/(const XRGB& c1, const XRGB& c2);
	friend XRGB operator+(const XRGB& c1, const XRGB& c2);
private:
	float m_r;
	float m_g;
	float m_b;
};


inline XRGB::XRGB(float red, float green, float blue)
: m_r(red), m_g(green), m_b(blue)
{
}

inline XRGB& XRGB::operator+=(const XRGB & right_op)
{
	*this = *this + right_op;
	return *this;
}

inline XRGB& XRGB::operator*=(float right_op)
{
	*this = *this * right_op;
	return *this;
}

inline XRGB& XRGB::operator/=(float right_op)
{
	*this = *this / right_op;
	return *this;
}

inline XRGB& XRGB::operator*=(const XRGB & right_op)
{
	*this = *this * right_op;
	return *this;
}


inline XRGB& XRGB::operator/=(const XRGB & right_op)
{
	*this = *this / right_op;
	return *this;
}

inline XRGB& XRGB::operator=(const XRGB & right_op)
{
	m_r = right_op.m_r;
	m_g = right_op.m_g;
	m_b = right_op.m_b;
	return *this;
}

inline void XRGB::clamp()
{
	if (m_r > 1.0f) 
		m_r = 1.0f;
	if (m_g > 1.0f) 
		m_g = 1.0f;
	if (m_b > 1.0f) 
		m_b = 1.0f;

	if (m_r < 0.0f) 
		m_r = 0.0f;
	if (m_g < 0.0f) 
		m_g = 0.0f;
	if (m_b < 0.0f) 
		m_b = 0.0f;
}

inline ostream& operator<<(ostream & out, const XRGB & the_rgb)
{
	out << the_rgb.m_r << ' '
		<< the_rgb.m_b << ' '
		<< the_rgb.m_b << ' ';

	return out;
}

inline XRGB operator*(const XRGB& c, float f)
{
	return XRGB(c.m_r*f, c.m_g*f, c.m_b*f);
}


inline XRGB operator*(float f, const XRGB& c)
{
	return XRGB(c.m_r*f, c.m_g*f, c.m_b*f);
}

inline XRGB operator/(const XRGB& c, float f)
{
	return XRGB(c.m_r/f, c.m_g/f, c.m_b/f);
}

inline XRGB operator/(const XRGB& c1, const XRGB& c2)
{
	return XRGB(c1.m_r/c2.m_r, c1.m_g/c2.m_g, c1.m_b/c2.m_b);
}

inline XRGB operator*(const XRGB& c1, const XRGB& c2)
{
	return XRGB(c1.m_r*c2.m_r, c1.m_g*c2.m_g, c1.m_b*c2.m_b);
}


inline XRGB operator+(const XRGB& c1, const XRGB& c2)
{
	return XRGB(c1.m_r+c2.m_r, c1.m_g+c2.m_g, c1.m_b+c2.m_b);
}
#endif
