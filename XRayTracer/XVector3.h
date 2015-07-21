/*
* Copyright (C) 2015 2nd Foundation
* All rights reserved
*
* The class for 3D vector implementation.
*/

#ifndef __X_VECTOR3_H
#define __X_VECTOR3_H

#include <math.h>
#include <iostream.h>

class XVector3
{
public:
	XVector3()
	{
	}

	XVector3(float e0, float e1, float e2);

	XVector3(const XVector3 &v)
	{
		*this = v;
	}

	float x() { return mElement[0]; }
	float y() { return mElement[1]; }
	float z() { return mElement[2]; }

	const XVector3& operator+() const;
	XVector3 operator-() const;
	float operator[](int i) const { return mElement[i]; }
	float& operator[](int i) { return mElement[i]; }

	float length() const;
	float squareLength() const;

	void makeUnitVector();

	void setX(float x)
	{
		mElement[0] = x;
	}
	
	void setY(float y)
	{
		mElement[1] = y;
	}
	
	void setZ(float z)
	{
		mElement[2] = z;
	}

	float minComponent() const;
	float maxComponent() const;
	float minAbsComponent() const;
	float maxAbsComponent() const;

	int indexOfMinComponent() const;
	int indexOfMinAbsComponent() const;
	int indexOfMaxComponent() const;
	int indexOfMaxAbsComponent() const;
private:
	float mElement[3];
};

#endif
