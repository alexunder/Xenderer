/*
* Copyright (C) 2015 2nd Foundation
* All rights reserved
*
* The mplementation of Sphere 
*/

#include "XSphere.h"


XSphere::XSphere(const XVector3 & center, float radius, const XRGB color)
	: mCenter(center), mRadius(radius), mColor(color)
{
}

//BBox bouldingBox() const;

bool XSphere::hit(const XRay & r, float tmin, float tmax, float time, HitRecord& record) const
{
	XVector3 temp = r.origin() - mCenter;

	double a = dot(r.direction(), r.direction());
	double b = 2*dot(r.direction(), temp);
	double c = dot(temp, temp) - mRadius*mRadius;

	double discriminant = b*b - 4*a*c;

	if (discriminant > 0)
	{
		discriminant = sqrt(discriminant);
		double t = (- b - discriminant) / (2*a);

		if (t < tmin)
			t = (- b + discriminant) / (2*a);

		if (t < tmin || t > tmax)
			return false;

		record.t = t;
		record.normal = unitVector(r.origin() + t*r.direction() - mCenter);
		record.color = mColor;
		return true;
	}
	
	return false;
}

bool XSphere::shadowHit(const XRay & r, float tmin, float tmax, float time) const
{
	XVector3 temp = r.origin() - mCenter;

	double a = dot(r.direction(), r.direction());
	double b = 2*dot(r.direction(), temp);
	double c = dot(temp, temp) - mRadius*mRadius;

	double discriminant = b*b - 4*a*c;

	if (discriminant > 0)
	{
		discriminant = sqrt(discriminant);
		double t = (- b - discriminant) / (2*a);

		if (t < tmin)
			t = (- b + discriminant) / (2*a);

		if (t < tmin || t > tmax)
			return false;

		return true;
	}
	
	return false;
}
