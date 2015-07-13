/*
* Copyright (C) 2015 2nd Foundation
* All rights reserved
*
* The class for generating image file.
*/

#include "XImage.h"
#include "iostream"

using namespace std;

XImage::XImage()
{

}

XImage::XImage(int width, iny height)
{
	mWidth = width;
	mHeight = height;

	//allocate memory for raster
	mRaster = new XRGB*[mWidth];

	int i;
	for (i = 0; i < m_width; i++)
		mRaster[i] = new XRGB[mHeight];
}

