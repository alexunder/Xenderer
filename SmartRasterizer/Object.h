/*
* Copyright (C) 2015 2nd Foundation
* All rights reserved
*/

#ifndef __H_OBJECT
#define __H_OBJECT

#include "Vector3f.h"
#include "Vector2f.h"
#include "Vector4f.h"

#include <vector>

using namespace std;

class TriangleMesh
{
public:
	Vector3f vertice[3];
	Vector3f normal[3];
	Vector2f uv[3];
};

class ObjectModel
{
public:
	ObjectModel();

	void AddMesh(TriangleMesh mesh);
	void SetWorldPosition(float x, float y, float z);
private:
	vector<TriangleMesh> meshlist;
	int num_mesh;
	Vector4f worldPosition;
};

#endif