/*
 * Copyright (C) 2015 2nd Foundation
 * All rights reserved
 */

#include "os_layer.h"
#include "stdafx.h"
#include "RendererCanvas.h"
#include "ModelLoader.h"

//#define TEST_DDA_LINE

char * input_file = NULL;
int    width = 800;
int    height = 800;
bool test_line_mode = false;
bool test_triangle_mode = false;
bool test_rasterize_triangle_mode = false;
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


int main (int argc, char *argv[]) {
    parseArgs(argc, argv);

    MeshObjectModel * pMesh = NULL;

    if (input_file != NULL) {
       bool ret = loadObjModel(input_file, &pMesh);

       if (ret == false) {
            fprintf(stderr, "Loaded OBJ file failed, just Exit.\n");
            return 1;
       }
    }

    gCanvas.CreateFrameBuffer(width, height);

    UIContext * pContext = new UIContext(width, height, &gCanvas);
    pContext->Init(argc, argv);

    if (test_line_mode == true || test_triangle_mode == true
                               || test_rasterize_triangle_mode == true ) {

        if (test_line_mode == true)
            test_draw_lines();

        if (test_triangle_mode == true)
            test_triangle_lines();

        if (test_rasterize_triangle_mode == true)
            test_triangle_rasterize();
    }

    pContext->Prepare();

    if (pMesh != NULL)
        delete pMesh;

    delete pContext;
    return 0;
}
