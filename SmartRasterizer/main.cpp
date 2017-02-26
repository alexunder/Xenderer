/*
 * Copyright (C) 2015 2nd Foundation
 * All rights reserved
 */

#include "os_layer.h"
#include "stdafx.h"
#include "RendererCanvas.h"
#include "ModelLoader.h"

char * input_file = NULL;
int    width = 800;
int    height = 600;
bool test_line_mode = false;
bool test_triangle_mode = false;
bool test_rasterize_triangle_mode = false;
bool test_rasterize_cubic_mode = false;
bool debug_dump = false;
char * debugDumpFile = NULL;
RendererCanvas gCanvas;

void parseArgs(int argc, char **argv) {
    for (int i = 1; i < argc; i++) {
        if (!strcmp(argv[i], "-input")) {
            i++;
            assert (i < argc);
            input_file = argv[i];
        } else if (!strcmp(argv[i], "-size")) {
            i++;
            assert (i < argc);
            width = atoi(argv[i]);
            i++;
            assert (i < argc);
            height = atoi(argv[i]);
        } else if (!strcmp(argv[i], "-testline")) {
            test_line_mode = true;
        } else if (!strcmp(argv[i], "-triangle")) {
            test_triangle_mode = true;
        } else if (!strcmp(argv[i], "-rastertriangle")) {
            test_rasterize_triangle_mode = true;
        } else if (!strcmp(argv[i], "-rastercubic")) {
            test_rasterize_cubic_mode = true;
        } else if (!strcmp(argv[i], "-debug")) {
            i++;
            assert (i < argc);
            debugDumpFile = argv[i];
        }
    }
}

void test_draw_lines() {
    //Draw x and y Axis
    Color colorAxis(0.0, 0.0, 0.0);
    Color colorLine(1.0, 0.0, 1.0);
    gCanvas.DrawLineWithBresenham(colorAxis, 0, height/2, width - 1, height/2);
    gCanvas.DrawLineWithBresenham(colorAxis, width/2, 0, width/2, height - 1);

    //Then draw 8 cases
#ifdef TEST_DDA_LINE
    gCanvas.DrawLineWithDDA(colorLine, width/2, height/2, width/2 + 200, height/2 + 50);
    gCanvas.DrawLineWithDDA(colorLine, width/2, height/2, width/2 + 50, height/2 + 200);
    gCanvas.DrawLineWithDDA(colorLine, width/2, height/2, width/2 - 200, height/2 - 50);
    gCanvas.DrawLineWithDDA(colorLine, width/2, height/2, width/2 - 50, height/2 - 200);

    gCanvas.DrawLineWithDDA(colorLine, width/2, height/2, width/2 + 200, height/2 - 50);
    gCanvas.DrawLineWithDDA(colorLine, width/2, height/2, width/2 + 50, height/2 - 200);
    gCanvas.DrawLineWithDDA(colorLine, width/2, height/2, width/2 - 200, height/2 + 50);
    gCanvas.DrawLineWithDDA(colorLine, width/2, height/2, width/2 - 50, height/2 + 200);
#else
    gCanvas.DrawLineWithBresenham(colorLine, width/2, height/2, width/2 + 200, height/2 + 50);
    gCanvas.DrawLineWithBresenham(colorLine, width/2, height/2, width/2 + 50, height/2 + 200);
    gCanvas.DrawLineWithBresenham(colorLine, width/2, height/2, width/2 - 200, height/2 - 50);
    gCanvas.DrawLineWithBresenham(colorLine, width/2, height/2, width/2 - 50, height/2 - 200);

    gCanvas.DrawLineWithBresenham(colorLine, width/2, height/2, width/2 + 200, height/2 - 50);
    gCanvas.DrawLineWithBresenham(colorLine, width/2, height/2, width/2 + 50, height/2 - 200);
    gCanvas.DrawLineWithBresenham(colorLine, width/2, height/2, width/2 - 200, height/2 + 50);
    gCanvas.DrawLineWithBresenham(colorLine, width/2, height/2, width/2 - 50, height/2 + 200);
#endif
}

void test_triangle_lines() {
    Color color(0.0, 0.0, 1.0);
    int x0 = 10;
    int y0 = 10;
    int x1 = 600;
    int y1 = 156;
    int x2 = 650;
    int y2 = 420;

    gCanvas.DrawLineWithBresenham(color, x0, y0, x1, y1);
    gCanvas.DrawLineWithBresenham(color, x1, y1, x2, y2);
    gCanvas.DrawLineWithBresenham(color, x2, y2, x0, y0);
}

void test_triangle_rasterize() {
    Color color(0.0, 0.0, 1.0);
    int x0 = 10;
    int y0 = 10;
    int x1 = 600;
    int y1 = 156;
    int x2 = 650;
    int y2 = 420;
    gCanvas.RasterizeTriangle(color, x0, y0, x1, y1, x2, y2);
}

void GenerateTextureForTest(unsigned int ** texture)
{
    unsigned int * buffer = *texture;
    int single = sizeof(unsigned int);
    buffer = (unsigned int *)malloc(256*256*single);
    int i;
    int j;
    for (j = 0; j < 256; j++)
    for (i = 0; i < 256; i++)
    {
        int x = i / 32, y = j / 32;
        buffer[j*256 + i] = ((x + y) & 1)? 0xffffff : 0x3fbcef;
    }
}

void debug_frameBuffer(char * FileName, int width, int height, unsigned int * buffer) {
    if (buffer == NULL || FileName == NULL)
        return;

    char *ext = &FileName[strlen(FileName)-4];
    assert(!strcmp(ext,".ppm"));
    FILE *file = fopen(FileName, "w");
    // misc header information
    assert(file != NULL);
    fprintf (file, "P6\n");
    fprintf (file, "# Creator: debug\n");
    fprintf (file, "%d %d\n", width, height);
    fprintf (file, "255\n");

    int y;
    int x;
    for (y = 0; y <= height; y++) {
        for (x = 0; x < width; x++) {
            unsigned int value = buffer[y*width + x];
            char a = (char)((0xff000000&value) >> 24);
            char r = (char)((0x00ff0000&value) >> 16);
            char g = (char)((0x0000ff00&value) >> 8);
            char b = (char)((0x000000ff&value));
            fputc(r, file);
            fputc(g, file);
            fputc(b, file);
        }
    }

    fclose(file);
}


int main (int argc, char *argv[])
{
    parseArgs(argc, argv);

    MeshObjectModel * pMesh = NULL;

    if (input_file != NULL)
    {
       bool ret = loadObjModel(input_file, &pMesh);

       if (ret == false)
       {
            fprintf(stderr, "Loaded OBJ file failed, just Exit.\n");
            return 1;
       }
    }

    UIContext * pContext = new UIContext(width, height);
    pContext->Init(argc, argv);

    if (test_line_mode == true || test_triangle_mode == true
                               || test_rasterize_triangle_mode == true )
    {
        gCanvas.CreateFrameBuffer(width, height);
        pContext->SetCanvas(&gCanvas);

        if (test_line_mode == true)
            test_draw_lines();

        if (test_triangle_mode == true)
            test_triangle_lines();

        if (test_rasterize_triangle_mode == true)
            test_triangle_rasterize();
    }

    RenderDevice * device = NULL;
    unsigned int * texture = NULL;
    if  (test_rasterize_cubic_mode == true)
    {
        device = new RenderDevice(width, height);
        pContext->SetRenderDevice(device);
        device->initCamera(3, 0, 0);
        GenerateTextureForTest(&texture);
//#ifdef __DEBUG
        debug_frameBuffer("texture.ppm", 256, 256, texture);
//#endif
        device->SetTexture(texture, 4, 256, 256);
        //device->SetRenderState(RENDERING_WIREFRAME);
        device->SetRenderState(RENDERING_COLOR);
        device->clear(0);
		device->DrawBox(0.0);
    }

    if (debugDumpFile != NULL)
    {
        unsigned int * fb = pContext->getFB();
        if (fb != NULL)
        {
            debug_frameBuffer(debugDumpFile, pContext->getWidth(),
                    pContext->getHeight(), fb);
        }
    }

    pContext->Prepare();

    if (pMesh != NULL)
        delete pMesh;
    if (device != NULL)
        delete device;
    if (texture != NULL)
        free(texture);

    delete pContext;
    return 0;
}
