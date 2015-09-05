/*
* Copyright (C) 2015 2nd Foundation
* All rights reserved
*
* The mplementation of Sphere 
*/

#include "XSphere.h"
#include <stdio.h>

XSphere::XSphere(const XVector3 & center, float radius, const XRGB color)
	: mCenter(center), mRadius(radius), mColor(color)
{
#ifdef DEBUG
	cout << "mCenter=" << mCenter<<endl;
	cout << "mRadius=" << mRadius<<endl;
	cout << "mColor="  << mColor<<endl;
#endif
}

//BBox bouldingBox() const;

bool XSphere::hit(const XRay & r, float tmin, float tmax, HitRecord& record) const
{
	XVector3 temp = r.origin() - mCenter;

	double a = dot(r.direction(), r.direction());
	double b = 2*dot(r.direction(), temp);
	double c = dot(temp, temp) - mRadius*mRadius;

#ifdef DEBUG
	cout << "temp="  << temp<<endl;
	printf("XSphere::hit, a=%f, b=%f, c=%f\n", a, b, c);	
#endif

	double discriminant = b*b - 4*a*c;

	if (discriminant > 0)
	{
		discriminant = sqrt(discriminant);
		double t = (- b - discriminant) / (2*a);

		if (t < tmin)
			t = (- b + discriminant) / (2*a);

		if (t < tmin || t > tmax)
			return false;

#ifdef DEBUG
		printf("XSphere::hit,there is a hit, t=%f\n", t);	
#endif
		record.t = t;
		record.normal = unitVector(r.origin() + t*r.direction() - mCenter);
		record.color = mColor;
		return true;
	}
	
	return false;
}

bool XSphere::shadowHit(const XRay & r, float tmin, float tmax) const
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
