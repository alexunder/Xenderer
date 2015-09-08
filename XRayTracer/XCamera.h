/*
* Copyright (C) 2015 2nd Foundation
* All rights reserved
*
* The implemantation of the camera class 
*/

#ifndef _X_CAMERA_H
#define _X_CAMERA_H

#include "XRay.h"
#include "XOrthonormalBasic.h"

class XCamera
{
public:
	XCamera(const XCamera& orig)
	{
		mCenter = orig.mCenter;
		mCorner = orig.mCorner;
		mAcross = orig.mAcross;
		mUp = orig.mUp;
		mUVW = orig.mUVW;;
		mLensRadius = orig.mLensRadius;
		mU0 = orig.mU0;
		mU1 = orig.mU1;
		mV0 = orig.mV0;
		mV1 = orig.mV1;
		mDistance = orig.mDistance;
	}

	XCamera(XVector3 c, XVector3 gaze, XVector3 vup, float aperture, float left, float right,
		float bottom, float top, float distance)
		: mCenter(c), mDistance(distance), mU0(left), mU1(right), mV0(bottom), mV1(top)
	{
		mLensRadius = aperture / 2.0;
		mUVW.initFromWV(-gaze, vup);
		mCorner = mCenter + mU0*mUVW.u() + mU1*mUVW.u() - mDistance*mUVW.w();
		mAcross = (mU0 - mU1) * mUVW.u();
		mUp = (mV0 - mV1) * mUVW.v();
	}

	XRay getRay(float a, float b, float x1, float x2)
	{
		XVector3 origin = mCenter + 2.0f * (x1 - 0.5f) * mLensRadius * mUVW.u() + 
				2.0 * (x2 - 0.5f) * mLensRadius * mUVW.v();

		XVector3 target = mCorner + mAcross * a + mUp * b;
		return XRay(origin, unitVector(target - origin));
	}
private:
	XVector3 mCenter;
	XVector3 mCorner;
	XVector3 mAcross;
	XVector3 mUp;

	XOrthonormalBasic mUVW;

	float mLensRadius;
	float mU0;
	float mU1;
	float mV0;
	float mV1;
	float mDistance;
};

#endif
