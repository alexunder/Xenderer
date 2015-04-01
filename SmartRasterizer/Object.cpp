/*
* Copyright (C) 2015 2nd Foundation
* All rights reserved
*/

#include "Object.h"

ObjectModel::ObjectModel()
{
	num_mesh = 0;
}

void ObjectModel::AddMesh(TriangleMesh mesh)
{
	meshlist.push_back(mesh);
	num_mesh++;
}

void ObjectModel::SetWorldPosition(float x, float y, float z)
{
	worldPosition = Vector4f(x, y, z, 1.0);
}