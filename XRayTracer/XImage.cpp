/*
* Copyright (C) 2015 2nd Foundation
* All rights reserved
*
* The class for generating image file.
*/

#include "XImage.h"

XImage::XImage()
{

}

XImage::XImage(int width, int height)
{
	mWidth = width;
	mHeight = height;

	//allocate memory for raster
	mRaster = new XRGB*[mWidth];

	int i;
	for (i = 0; i < mWidth; i++)
		mRaster[i] = new XRGB[mHeight];
}

XImage::XImage(int width, int height, XRGB background)
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

XImage::~XImage()
{
	destroyRaster();
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
	float power = 1.0 / gamma;

	int i;
	int j;

	for ( i = 0; i < mWidth; i++)
	for ( j = 0; j < mHeight; j++)
	{
		temp = mRaster[i][j];
		mRaster[i][j] = XRGB(pow(temp.r(), power),
							 pow(temp.g(), power),
							 pow(temp.b(), power));
	}
}

void XImage::writePPM(ostream& out)
{
	//output header
	out << "P6\n";
	out << mWidth << ' ' << mHeight << '\n';
	out << "255\n";

	int i;
	int j;
	unsigned int ired, igreen, iblue;
	unsigned char red, green, blue;

	//output clamped [0, 255] values
	for (i = mHeight - 1; i >= 0; i--)
	for (j = 0; j < mWidth; j++)
	{
		ired   = (unsigned int)(256*mRaster[j][i].r());
		igreen = (unsigned int)(256*mRaster[j][i].g());
		iblue  = (unsigned int)(256*mRaster[j][i].b());

		if (ired > 255)
			ired = 255;
		if (igreen > 255)
			igreen = 255;
		if (iblue > 255)
			iblue = 255;

		red   = (unsigned char)(ired);
		green = (unsigned char)(igreen);
		blue = (unsigned char)(iblue);

		out.put(red);
		out.put(green);
		out.put(blue);
	}
}

void XImage::destroyRaster()
{
	if (mRaster == NULL)
		return;

	int i;
	for (i = 0; i < mWidth; i++)
	{
		if (mRaster[i] != NULL)
		{
			delete mRaster[i];
			mRaster[i] = NULL;
		}
	}

	delete mRaster;
	mRaster = NULL;
}

//reads in a binary PPM
void XImage::readPPM(string file_name)
{
	//open stream to file
	ifstream in;
	in.open(file_name.c_str());

	if (!in.is_open())
	{
		cerr << "ERROR -- Couldn't open file \'" << file_name <<"\'.\n";
		return;
	}
	
	char ch, type;
	char red, green, blue;
	int i, j, cols, rows;
	int num;

	//read in header info
	in.get(ch);
	in.get(type);
	in >> cols >> rows >> num;

	mWidth  = cols;
	mHeight = rows;

	destroyRaster();
	//allocate raster
	mRaster = new XRGB*[mWidth];
	for (i = 0; i < mWidth; i++)
		mRaster[i] = new XRGB[mHeight];

	//clean up newline
	in.get(ch);
	//store PPM pixel values in raster
	for (i = mHeight - 1; i >= 0; i--)
	for (j = 0; j < mWidth; j++)
	{
		in.get(red);
		in.get(green);
		in.get(blue);

		mRaster[j][i] = XRGB((float)((unsigned char)red)/255.0,
							 (float)((unsigned char)green)/255.0,
							 (float)((unsigned char)blue)/255.0);
	}
}
