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

unsigned int * GenerateTextureForTest()
{
    int single = sizeof(unsigned int);
    unsigned int * buffer = (unsigned int *)malloc(256*256*single);
    int i;
    int j;
    for (j = 0; j < 256; j++)
    for (i = 0; i < 256; i++)
    {
        int x = i / 32, y = j / 32;
        buffer[j*256 + i] = ((x + y) & 1)? 0xffffff : 0x3fbcef;
    }
    return buffer;
}

void debug_frameBuffer(char * FileName, int width, int height,
                        unsigned int * buffer, bool isRGBOrder)
{
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
            char a, r, g, b;
            a = (char)(((0xff << 24) & value) >> 24);
            g = (char)(((0xff << 8) & value) >> 8);

            if (isRGBOrder)
            {
                b = (char)((0xff & value));
                r = (char)(((0xff << 16) & value) >> 16);
            }
            else
            {
                r = (char)((0xff & value));
                b = (char)(((0xff << 16) & value) >> 16);
            }
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
        pContext->Prepare();
    }

    RenderDevice * device = NULL;
    unsigned int * texture = NULL;
    if  (test_rasterize_cubic_mode == true)
    {
        float alpha = 1;
        float pos = 3.5;
        int indicator = 0;
        int kbhit = 0;
        int render_states[] = { RENDERING_WIREFRAME,
                                RENDERING_TEXTURE,
                                RENDERING_COLOR };
        device = new RenderDevice(width, height);
        pContext->SetRenderDevice(device);
        device->initCamera(3.5, 0, 0);
        texture = GenerateTextureForTest();
        device->SetTexture(texture, 4, 256, 256);
        pContext->Prepare();
        //device->SetRenderState(RENDERING_COLOR);
        int keyState;
        //while (!pContext->isQuit())
        {
#ifdef __DEBUG
            cout<<"Rendering loop!"<<endl;
#endif
            device->clear(1);
            device->initCamera(pos, 0, 0);
            /*
            keyState = pContext->getKeyPressState();
            switch(keyState)
            {
                case KEYPRESS_UP:
                    printf("Up\n");
                    pos -= 0.01f;
                    break;
                case KEYPRESS_LEFT:
                    alpha += 0.01f;
                    printf("Left\n");
                    break;
                case KEYPRESS_RIGHT:
                    alpha -= 0.01f;
                    printf("Right\n");
                    break;
                case KEYPRESS_DOWN:
                    printf("Down\n");
                    pos -= 0.01f;
                    break;
                case KEYPRESS_SPACE:
                    printf("Space\n");
                    if (kbhit == 0)
                    {
                        kbhit = 1;
                        if (++indicator >= 3) indicator = 0;
                        device->SetRenderState((RenderState)render_states[indicator]);
                    }
                    else
                    {
                        kbhit = 0;
                    }
                    break;
            }
            */
            device->DrawBox(alpha);
            pContext->InvalidateArea();
            pContext->mainloop();
        }
    }

    if (debugDumpFile != NULL)
    {
        unsigned int * fb = pContext->getFB();
        if (fb != NULL)
        {
            debug_frameBuffer(debugDumpFile, pContext->getWidth(),
                    pContext->getHeight(), fb, false);
        }
    }


    if (pMesh != NULL)
        delete pMesh;
    if (device != NULL)
        delete device;
    if (texture != NULL)
        free(texture);

    delete pContext;
    return 0;
}
