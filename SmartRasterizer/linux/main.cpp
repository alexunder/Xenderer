/*
 * Copyright (C) 2015 2nd Foundation
 * All rights reserved
 */

#include <cairo.h>
#include <gtk/gtk.h>
#include "stdafx.h"
#include "RendererCanvas.h"
#include "ModelLoader.h"

char * input_file = NULL;
int    width = 800;
int    height = 800;
bool testmode = false;
RendererCanvas gCanvas;

gboolean on_expose_event (GtkWidget * widget, GdkEventExpose *event, 
                                                      gpointer data)
{
	cairo_t *cr = gdk_cairo_create(widget->window);
	GdkPixbuf * pixframebuffer = gdk_pixbuf_new_from_data(
                        (const unsigned char*)gCanvas.getframeBuffer(), 
						GDK_COLORSPACE_RGB, TRUE, 8, width, height,
						width*4, NULL, NULL);
	gdk_cairo_set_source_pixbuf(cr, pixframebuffer, 0, 0);
	cairo_paint(cr);
	g_object_unref(pixframebuffer);

	cairo_destroy(cr);
	return FALSE;
}

void parseArgs(int argc, char **argv)
{
    for (int i = 1; i < argc; i++)
    {
        if (!strcmp(argv[i], "-input"))
        {
            i++;
            assert (i < argc);
            input_file = argv[i];
        }
        else if (!strcmp(argv[i], "-size"))
        {
            i++;
            assert (i < argc);
            width = atoi(argv[i]);
            i++;
            assert (i < argc);
            height = atoi(argv[i]);
        }
        else if (!strcmp(argv[i], "-testline"))
        {
            testmode = true;
        }
    }
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

    if (testmode == true)
	{
        gtk_init (&argc, &argv);

        gCanvas.CreateFrameBuffer(width, height);
        //Color color1(0.0,0.0,1.0);
        //gCanvas.DrawLineWithDDA(color1, 2, 2, 200, 500);
        //Draw x and y Axis
        Color colorAxis(0.0, 0.0, 0.0);
        Color colorLine(1.0, 0.0, 1.0);
        gCanvas.DrawLineWithBresenham(colorAxis, 0, height/2, width - 1, height/2);
        //gCanvas.DrawLineWithDDA(colorAxis, 0, height/2, width - 1, height/2);
        gCanvas.DrawLineWithBresenham(colorAxis, width/2, 0, width/2, height - 1);
        //gCanvas.DrawLineWithDDA(colorAxis, width/2, 0, width/2, height - 1);

        //Then draw 8 cases
        gCanvas.DrawLineWithBresenham(colorLine, width/2, height/2, width/2 + 200, height/2 + 50);
        gCanvas.DrawLineWithBresenham(colorLine, width/2, height/2, width/2 + 50, height/2 + 200);
        gCanvas.DrawLineWithBresenham(colorLine, width/2, height/2, width/2 - 200, height/2 - 50);
        gCanvas.DrawLineWithBresenham(colorLine, width/2, height/2, width/2 - 50, height/2 - 200);

        gCanvas.DrawLineWithBresenham(colorLine, width/2, height/2, width/2 + 200, height/2 - 50);
        gCanvas.DrawLineWithBresenham(colorLine, width/2, height/2, width/2 + 50, height/2 - 200);
        gCanvas.DrawLineWithBresenham(colorLine, width/2, height/2, width/2 - 200, height/2 + 50);
        gCanvas.DrawLineWithBresenham(colorLine, width/2, height/2, width/2 - 50, height/2 + 200);

        GtkWidget *window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
        g_signal_connect(window, "destroy", G_CALLBACK (gtk_main_quit), NULL);
        gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
        gtk_widget_set_size_request(window, width, height);
        gtk_window_set_resizable(GTK_WINDOW(window), FALSE);

        g_signal_connect(window, "expose-event", G_CALLBACK(on_expose_event), NULL);
        gtk_widget_set_app_paintable(window, TRUE);
        gtk_widget_show_all(window);
        gtk_main();
    }

    if (pMesh != NULL)
        delete pMesh;

    return 0;
}
