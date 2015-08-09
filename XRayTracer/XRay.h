/*Copyright (C) 2015 2nd Foundation
* All rights reserved
*
* The class for Ray.
*/

#ifndef _X_RAY_H
#define _X_RAY_H

#include "XVector.h"

class XRay
{
public:
	Xray(const XVector3& a, const XVector3& b)
	{
		mData[0] = a;	
		mData[1] = b;	
	}

	XRay(const XRay & r)
	{
		*this = r;
	}

	XVector3 origin() const
	{
		return mData[0];
	}
	
	XVector3 direction() const
	{
		return mData[1];
	}

	XVector3 pointAtParameter(float t) const
	{
		return mData[0] + t*mData[1];
	}
private:
	XVector3 mData[2];
};

inline ostream &operator<<(ostream &os, const XRay &r)
{
	os << "(" << r.origin() << ") + t(" << r.direction() << ")";
	return os;
}
#endif
