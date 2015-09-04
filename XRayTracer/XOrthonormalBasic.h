/*
* Copyright (C) 2015 2nd Foundation
* All rights reserved
*
* The implementation of Orthonormal Basic Class
*/

#ifndef __X_ORTHONORMALBASIC_H
#define __X_ORTHONORMALBASIC_H

#include "XVector3.h"

class OrthonormalBasic
{
public:
	OrthonormalBasic()
	{
	}

	OrthonormalBasic(const XVector3& a, const XVector3& b, const XVector3& c)
	{
		mU = a;
		mV = b;
		mW = c;
	}
	
	void initFromU(const XVector3& u);
	void initFromV(const XVector3& v);
	void initFromW(const XVector3& w);

	void set(const XVector3& a, const XVector3& b, const XVector3& c)
	{
		mU = a;
		mV = b;
		mW = c;
	}

	void initFromUV( const XVector3& u, const XVector3& v);
	void initFromVU( const XVector3& v, const XVector3& u);
	
	void initFromUW( const XVector3& u, const XVector3& w);
	void initFromWU( const XVector3& w, const XVector3& u);

	void initFromVW( const XVector3& v, const XVector3& w);
	void initFromWV( const XVector3& w, const XVector3& v);

	friend istream &operator>>(istream & is, OrthonormalBasic &t);
	friend ostream &operator<<(ostream & os, const OrthonormalBasic &t);

	friend bool operator==(const OrthonormalBasic & o1,const OrthonormalBasic & o2);
	
	XVector3 u() const
	{
		return mU;
	}
	
	XVector3 v() const
	{
		return mV;
	}
	XVector3 w() const
	{
		return mW;
	}
private:
	XVector3 mU;
	XVector3 mV;
	XVector3 mW;
};

#endif
