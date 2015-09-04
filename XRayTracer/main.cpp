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
	HitRecord rec;
	bool is_a_hit;

	float tmax;
	XVector3 dir(0, 0, -1);

	//geometry
	vector<XShape*> shapes;
	shapes.push_back(new XSphere(XVector3(250, 250, -1000), 150, XRGB(.2, .2, .8)));
	shapes.push_back(new XTriangle(XVector3(300.0f, 600.0f, -800),
								   XVector3(0.0f, 100.0f, -1000),
								   XVector3(450.0f, 20.0f, -1000),
								   XRGB(.8, .2, .2)) );

	XImage im(500, 500);

	//loop over pixel
	int i;
	int j;
	int k;

	for (i = 0; i < 500; i++)
	for (j = 0; j < 500; j++)
	{
		tmax = 100000.0f;
		is_a_hit = false;

		XRay r(XVector3(i, j, 0), dir);

		//loop over list of shapes
		for (k = 0; k < shapes.size(); k++)
		{
			if (shapes[k]->hit(r, 0.00001f, tmax, rec))
			{
				//printf("Hit the shape, i=%d, j=%d\n", i, j);
				tmax = rec.t;
				is_a_hit = true;
			}
		}

		if (is_a_hit)
			im.setPixel(i, j, rec.color);
		else
			im.setPixel(i, j, XRGB(1.0, 1.0, 1.0));
	}
	
	ofstream file;
	file.open("image.ppm");		
	im.writePPM(file);
	file.close();
}
