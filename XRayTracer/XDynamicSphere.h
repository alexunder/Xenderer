/*
* Copyright (C) 2015 2nd Foundation
* All rights reserved
*
* The class for DynamicSphere 
*/

#ifndef _X_DYNAMIC_SPHERE_H
#define _X_DYNAMIC_SPHERE_H

#include "XShape.h"
#include "XVector3.h"
#include "XRay.h"
#include "rgb.h"

class XDynamicSphere : public XShape
{
public:
	XDynamicSphere(const XVector3 & center, float radius, const XRGB color,
		float min_time, float max_time);
	bool hit(const XRay & r, float tmin, float tmax, HitRecord& record) const;
	bool shadowHit(const XRay & r, float tmin, float tmax) const;
	XVector3 getCenter(float time) const;
private:
	XVector3 mCenter;
	float mRadius;
	XRGB  mColor;
}; 

#endif
