/*
* Copyright (C) 2015 2nd Foundation
* All rights reserved
*
* The class for dynamic array.
*/

#ifndef _X_DYNAMICARRAY_H
#define _X_DYNAMICARRAY_H

template <class T> class DynamicArray
{
public:
	DynamicArray();
	DynamicArray(int a);
	~DynamicArray();

	bool append(T item);
	bool truncate();
	void clear()
	{
		mData = 0;
	}

	int length() const
	{
		return mnData;
	}

	bool empty() const
	{
		return mnData == 0;
	}

	const T &operator[](int i) const
	{
		return mData[i];
	}

	T &operator[](int i)
	{
		return mData[i];
	}
private:
	T * mData;
	int mnData;
	int mArraySize;
};

template <class T> DynamicArray<T>::DynamicArray()
{
	mnData = 0;
	mArraySize = 4;
	mData = new T[mArraySize];
}

template <class T> DynamicArray<T>::DynamicArray(int a)
{
	mnData = 0;
	mArraySize = a;
	mData = new T[mArraySize];
}

template <class T> DynamicArray<T>::~DynamicArray()
{
	mnData = 0;
	delete [] mData;
}

template <class T> bool DynamicArray<T>::truncate()
{
	if (mnData != mArraySize)
	{
		T * temp = mData;
		mArraySize = mnData;

		if (!(mData = new T[mArraySize]))
			return false;
		
		int i;
		for (i = 0; i < mnData; i++)
			mData[i] = temp[i];

		delete [] temp;
	}

	return true;
}

template <class T> bool DynamicArray<T>::append(T item)
{
	if (mnData == mArraySize)
	{
		mArraySize *= 2;
		T * temp = data;

		if (!(mData = new T[mArraySize]))
			return false;
		
		int i;
		for (i = 0; i < mnData; i++)
			mData[i] = temp[i];

		delete [] temp;
	}

	mData[mnData++] = item;
	return true;
}
#endif
