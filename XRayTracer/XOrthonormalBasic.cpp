/*
* Copyright (C) 2015 2nd Foundation
* All rights reserved
*
* The implementation of Orthonormal Basic Class
*/

#include "XOrthonormalBasic.h"

#define ONB_EPSILON 0.01f

void OrthonormalBasic::initFromU(const XVector3& u)
{
	XVector3 n(1.0f, 0.0f, 0.0f);
	XVector3 m(0.0f, 1.0f, 0.0f);

	mU = unitVector(u);
	mV = cross(mU, n);

	if (mV.length() < ONB_EPSILON)
		mV = cross(mU, m);

	mW = cross(mU, mV);
}

void OrthonormalBasic::initFromV(const XVector3& v)
{
	XVector3 n(1.0f, 0.0f, 0.0f);
	XVector3 m(0.0f, 1.0f, 0.0f);

	mV = unitVector(v);
	mU = cross(mV, n);

	if (mU.squaredlength() < ONB_EPSILON)
		mU = cross(mV, m);

	mW = cross(mU, mV);
}

void OrthonormalBasic::initFromW(const XVector3& w)
{
	XVector3 n(1.0f, 0.0f, 0.0f);
	XVector3 m(0.0f, 1.0f, 0.0f);

	mW = unitVector(w);
	mU = cross(mW, n);

	if (mU.length() < ONB_EPSILON)
		mU = cross(mW, m);

	mV = cross(mW, mU);
}


