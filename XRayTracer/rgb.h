/*
* Copyright (C) 2015 2nd Foundation
* All rights reserved
*
* The class for RGB operations
*/

#ifndef  __X_RGB_H
#define  __X_RGB_H

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
ptivate:
	float m_r;
	float m_g;
	float m_b;
};

#endif
