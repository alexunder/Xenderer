/*
* Copyright (C) 2015 2nd Foundation
* All rights reserved
*
* The class for Sphere 
*/

#ifndef _X_SPHERE_H
#define _X_SPHERE_H

#include "XShape.h"
#include "XVector3.h"
#include "XRay.h"
#include "rgb.h"

class XSphere : public XShape
{
public:
	XSphere(const XVector3 & center, float radius, const XRGB color);
	//BBox bouldingBox() const;
	bool hit(const XRay & r, float tmin, float tmax, float time, HitRecord& record) const;
	bool shadowHit(const XRay & r, float tmin, float tmax, float time) const;
private:
	XVector3 mCenter;
	float mRadius;
	XRGB  mColor;
}; 

#endif
