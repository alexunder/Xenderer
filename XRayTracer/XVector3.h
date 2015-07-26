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

	friend bool operator==(const XVector3& v1, const XVector3$ v2);
	friend bool operator=!(const XVector3& v1, const XVector3$ v2);

	friend istream &operator>>(istream &is, XVector3 &t);
	friend ostream &operator<<(ostream &os, const XVector3 &t);

	friend XVector3 operator+(const XVector3& v1, const XVector3& v2);
	friend XVector3 operator-(const XVector3& v1, const XVector3& v2);
	friend XVector3 operator/(const XVector3& vec, float scalar);
	friend XVector3 operator*(const XVector3& vec, float scalar);
	friend XVector3 operator*(float scalar, const XVector3& vec);

	XVector3& operator=(const XVector3& v2);
	XVector3& operator+=(const XVector3& v2);
	XVector3& operator-=(const XVector3& v2);
	XVector3& operator*=(const float t);
	XVector3& operator/=(const float t);

	friend XVector3 unitVector(const XVector3& v);
	friend XVector3 minVec(const XVector3& v1, const XVector3& v2);
	friend XVector3 maxVec(const XVector3& v1, const XVector3& v2);
	friend XVector3 cross(const XVector3& v1, const XVector3& v2);
	friend float dot(const XVector3& v1, const XVector3& v2);
	friend float tripleProduct(const XVector3& v1, const XVector3& v2, const XVector3 v3);
private:
	float mElement[3];
};

inline XVector3::XVector3(float e0, float e1, float e2)
{
	mElement[0] = e0;
	mElement[1] = e1;
	mElement[2] = e2;
}

inline const XVector3& XVector3::operator+() const
{
	return *this;
}

inline XVector3 XVector3::operator-() const
{
	return XVector3(-mElement[0], -mElement[1], -mElement[2]);
}

inline float XVector3::length() const
{
	return sqrt(mElement[0]*mElement[0] +  mElement[1]*mElement[1] + mElement[2]*mElement[2]);
}

inline float XVector3::squaredLength() const
{
	return mElement[0]*mElement[0] +  mElement[1]*mElement[1] + mElement[2]*mElement[2];
}

inline void XVector3::makeUnitVector()
{
	*this = *this / (*this).length();
}

inline float XVector3::minComponent() const
{
	float temp = mElement[0];

	if (mElement[1] < temp)
		temp = mElement[1];
	
	if (mElement[2] < temp)
		temp = mElement[2];
	
	return temp;
}

inline float XVector3::maxComponent() const
{
	float temp = mElement[0];

	if (mElement[1] > temp)
		temp = mElement[1];
	
	if (mElement[2] > temp)
		temp = mElement[2];
	
	return temp;
}

inline float XVector3::maxAbsComponent() const
{
	float temp = fabs(mElement[0]);

	if (fabs(mElement[1]) > temp)
		temp = fabs(mElement[1]);
	
	if (fabs(mElement[2]) > temp)
		temp = fabs(mElement[2]);
	
	return temp;
}

inline float XVector3::minAbsComponent() const
{
	float temp = fabs(mElement[0]);

	if (fabs(mElement[1]) < temp)
		temp = fabs(mElement[1]);
	
	if (fabs(mElement[2]) < temp)
		temp = fabs(mElement[2]);
	
	return temp;
}

inline int XVector3::indexOfMinComponent() const
{
	int index = 0;
	float temp = mElement[0];

	if(mElement[1] < temp)
	{
		temp = mElement[1];
		index = 1;
	}

	if(mElement[2] < temp)
		index = 2;

	return index;
}

inline int XVector3::indexOfMinAbsComponent() const
{
	int index = 0;
	float temp = fabs(mElement[0]);

	if(fabs(mElement[1]) < temp)
	{
		temp = fabs(mElement[1]);
		index = 1;
	}

	if(fabs(mElement[2]) < temp)
		index = 2;

	return index;
}

inline bool operator==(const XVector3& v1, const XVector3& v2)
{
	if (v1.x() != v2.x())
		return false;
	
	if (v1.y() != v2.y())
		return false;
	
	if (v1.z() != v2.z())
		return false;

	return true;
}

inline bool operator!=(const XVector3& v1, const XVector3& v2)
{
	return !(v1 == v2);
}

inline int XVector3::indexOfMaxComponent() const
{
	int index = 0;
	float temp = mElement[0];

	if(mElement[1] > temp)
	{
		temp = mElement[1];
		index = 1;
	}

	if(mElement[2] > temp)
		index = 2;

	return index;
}

inline int XVector3::indexOfMaxAbsComponent() const
{
	int index = 0;
	float temp = fabs(mElement[0]);

	if(fabs(mElement[1]) > temp)
	{
		temp = fabs(mElement[1]);
		index = 1;
	}

	if(fabs(mElement[2]) > temp)
		index = 2;

	return index;
}

inline XVector3 operator*(float scalar, const XVector3& vec)
{
	return XVector3(vec.x()*scalar, vec.y()*scalar, vec.z()*scalar);
}

inline XVector3 operator*(const XVector3& vec, float scalar)
{
	return XVector3(vec.x()*scalar, vec.y()*scalar, vec.z()*scalar);
}

inline XVector3 operator/(const XVector3& vec, float scalar)
{
	return XVector3(vec.x()/scalar, vec.y()/scalar, vec.z()/scalar);
}

inline XVector3 operator+(const XVector3& v1, const XVector3& v2)
{
	return XVector(v1.x() + v2.x(), v1.y() + v2.y(), v1.z() + v2.z());
}

inline XVector3 operator-(const XVector3& v1, const XVector3& v2)
{
	return XVector(v1.x() - v2.x(), v1.y() - v2.y(), v1.z() - v2.z());
}

#endif
