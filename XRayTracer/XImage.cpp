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

XImage::XImage(int width, iny height, XRGB background)
{
	mWidth = width;
	mHeight = height;

	//allocate memory for raster
	mRaster = new XRGB*[mWidth];

	int i;
	int j;

	for (i = 0; i < mWidth; i++)
	{
		mRaster[i] = new XRGB[mHeight];
		//Assign 'background' to each element.
		for (j = 0; i < mHeight; i++)
			mRaster[i][j] = background;;
	}
}

bool XImage::setPixel(int x, int y, const XRGB & color)
{
	//Check for out of boulds error
	if ( x < 0 || x > mWidth)
		return false;
	if ( y < 0 || y > mHeight)
		return false;

	mRaster[x][y] = color; 
}

void XImage::gammaCorrect(float gamma)
{
	XRGB temp;
	float power = 1.0 / gama;

	int i;
	int j;

	for ( i = 0; i < mWidth; i++)
	for ( j = 0; j < mHeight; j++)
	{
		temp = mRaster[i][j];
		mRaster[i][j] = XRGB(pow(temp.r(), power),
							 pow(temp.g(), power),
							 pow(temp.b(), power),
							 );
	}
}
