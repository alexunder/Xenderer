/*
* Copyright (C) 2015 2nd Foundation
* All rights reserved
*
* The class for generating image file.
*/

#ifndef __X_IMAGE_H
#define __X_IMAGE_H

#include <cmath>
#include <string>
#include <fstream>
#include "rgb.h"

using namespace std;

class XImage
{
public:
	XImage();
	//initializes raster to default color
	XImage(int width, int height);
	//initializes raster to 'background'
	XImage(int width, int height, XRGB background);

	~XImage();
	//return false if x or y are out of bounds, else true
	bool setPixel(int x, int y, const XRGB & color);
	void gammaCorrect(float gamma);
	//outputs PPM image to 'out'
	void writePPM(ostream& out);
	void readPPM(string file_name);
private:
	void destroyRaster();
private:
	XRGB** mRaster;
	int mWidth;
	int mHeight;
};

#endif
