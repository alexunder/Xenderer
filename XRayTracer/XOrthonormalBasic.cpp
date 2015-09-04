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

	if (mU.squareLength() < ONB_EPSILON)
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

void OrthonormalBasic::initFromUV( const XVector3 & u, const XVector3 & v)
{
	mU = unitVector(u);
	mW = unitVector( cross(u, v) );
	mV = cross(mU, mW);
}

void OrthonormalBasic::initFromVU( const XVector3 & v, const XVector3 & u)
{
	mV = unitVector(v);
	mW = unitVector( cross(u, v) );
	mU = cross(mV, mW);
}

void OrthonormalBasic::initFromUW( const XVector3 & u, const XVector3 & w)
{
	mU = unitVector(u);
	mV = unitVector( cross(u, w) );
	mW = cross(mU, mV);
}

void OrthonormalBasic::initFromWU( const XVector3 & w, const XVector3 & u)
{
	mW = unitVector(w);
	mV = unitVector( cross(u, w) );
	mU = cross(mV, mW);
}

void OrthonormalBasic::initFromVW( const XVector3 & v, const XVector3 & w)
{
	mV = unitVector(v);
	mU = unitVector( cross(v, w) );
	mW = cross(mU, mV);
}

void OrthonormalBasic::initFromWV( const XVector3 & w, const XVector3 & v)
{
	mW = unitVector(w);
	mU = unitVector( cross(v, w) );
	mV = cross(mU, mW);
}

bool operator==(const OrthonormalBasic & o1, const OrthonormalBasic & o2)
{
	return (o1.u() == o2.u() && o1.v() == o2.v() && o1.w() == o2.w());
}

istream & operator>>(istream & is, OrthonormalBasic & t)
{
	XVector3 newU;
	XVector3 newV;
	XVector3 newW;

	is >> newU >> newV >> newW;
	t.initFromUV(newU, newV);

	return is;
}

ostream & operator<<(ostream & os, const OrthonormalBasic & t)
{
	os << t.u() << "\n" << t.v() << "\n" << t.w() << "\n";
	return os;
}
