/*Copyright (C) 2015 2nd Foundation
* All rights reserved
*
* The class for dynamic array.
*/

#ifndef __X_SHAPE_H
#define __X_SHAPE_H

#include "XRay.h"
#include "XVector3.h"
#include "rgb.h"

class XRay;
class XRGB;

struct HitRecord
{
	float t;
	XVector3 normal;
	XRGB color;
};

class XShape
{
public:
	virtual bool hit(const XRay & r, float tmin, float tmax, float time, HitRecord& record) const=0;
	virtual bool shadowHit(const XRay & r, float tmin, float tmax, float time) const=0;
};

#endif
