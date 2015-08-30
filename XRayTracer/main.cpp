/*
* Copyright (C) 2015 2nd Foundation
* All rights reserved
*
* A simple sample 
*/

#include <vector>
#include <iostream>
#include "XVector3.h"
#include "rgb.h"
#include "XImage.h"
#include "XShape.h"
#include "XTriangle.h"
#include "XSphere.h"

using namespace std;

int main()
{
	HitRecor rec;
	bool is_a_hit;

	float tmax;
	XVector3 dir(0, 0, -1);

	//geometry
	vector<XShape*> shapes;
	shaped.push_back(new XSphere(XVector3(250, 250, -1000), 150, XRGB(.2, .2, .8)));
	shaped.push_back(new XTriangle(XVector3(300.0f, 600.0f, -800),
								   XVector3(0.0f, 100.0f, -1000),
								   XVector3(450.0f, 20.0f, -1000),
								   XRGB(.8, .2, .2)) );

	XImage im(500, 500);

}
