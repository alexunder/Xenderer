/*
* Copyright (C) 2015 2nd Foundation
* All rights reserved
*
* The class for generating random number.
*/

#ifndef _X_RNG_H
#define _X_RNG_H

class RandomNumberGenerator
{
public:
	RandomNumberGenerator(unsigned long long _seed = 7564231ULL)
	{
		mSeed = _seed;
		mMult = 62089911ULL;
		mllong_max = 4294967295ULL;
		mfloat_max = 4294967295.0f;
	}

	float operator() ();
private:
	unsigned long long mSeed;
	unsigned long long mMult;
	unsigned long long mllong_max;
	float mfloat_max;
};

inline float RandomNumberGenerator::operator()()
{
	mSeed = mMult * mSeed;
	return float(mSeed % mllong_max) / mfloat_max;
}
#endif
