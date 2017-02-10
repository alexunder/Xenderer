/*
 * Copyright (C) 2015 2nd Foundation
 * All rights reserved
 */

#include "RenderDevice.h"
#include "MeshObjectModel.h"

RenderDevice::RenderDevice(int width, int height)
{
    init(width, height);
}

void RenderDevice::init(int width, int height)
{
    
}

void RenderDevice::DrawFragment(MeshObjectModel * pObj)
{

}

//For test only
void RenderDevice::DrawBox()
{

}

void RenderDevice::DrawPrimitive(Vertex *p1, Vertex *p2, Vertex *p3)
{

}

void RenderDevice::DrawPixel(int x, int y, const Color &c)
{

}
