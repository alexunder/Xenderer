/*
* Copyright (C) 2015 2nd Foundation
* All rights reserved
*
* The class for Triangle 
*/

#ifndef _X_TRIANGLE_H
#define _X_TRIANGLE_H

#include "XShape.h"
#include "XVector3.h"
#include "rgb.h"
#include "XRay.h"

class XTriangle : public XShape
{
public:
	XTriangle(const XVector3 & p0, const XVector3 & p1, const XVector3 & p2, const XRGB & color);
	bool hit(const XRay & r, float tmin, float tmax, float time, HitRecord& record) const;
	bool shadowHit(const XRay & r, float tmin, float tmax, float time) const;
private:
	XVector3 mP0;
	XVector3 mP1;
	XVector3 mP2;
	XRGB mColor;
};
#endif
