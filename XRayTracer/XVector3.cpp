/*
* Copyright (C) 2015 2nd Foundation
* All rights reserved
*
*/

#include "XVector3.h"

using namespace std;

istream & operator>>(istream &is, XVector3 &t)
{
	float temp;

	is >> temp;
	t.setX(temp);
	is >> temp;
	t.setY(temp);
	is >> temp;
	t.setZ(temp);

	return is;
}

ostream & operator<<(ostream &os, const XVector3 &t)
{
	os << '(' <<t.x() << " "
			  <<t.y() << " "
			  <<t.z() << ')';

	return os;
}

float tripleProduct(const XVector3 &v1, const XVector3 &v2, const XVector3 &v3)
{
	return dot((cross(v1, v2)), v3);
}
