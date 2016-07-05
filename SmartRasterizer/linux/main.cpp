/*
 * Copyright (C) 2015 2nd Foundation
 * All rights reserved
 */

#include <cairo.h>
#include <gtk/gtk.h>
#include "stdafx.h"
#include "RendererCanvas.h"

char * input_file = NULL;
int    width = 800;
int    height = 800;
int gWidth = 800;
int gHeight = 600;
bool testmode = false;
RendererCanvas gCanvas;

gboolean on_expose_event (GtkWidget * widget, GdkEventExpose *event, gpointer data)
{
	cairo_t *cr = gdk_cairo_create(widget->window);
	GdkPixbuf * pixframebuffer = gdk_pixbuf_new_from_data((const unsigned char*)gCanvas.getframeBuffer(), 
														  GDK_COLORSPACE_RGB, 
														  TRUE, 
														  8, 
														  width,
														  height,
														  width*4,
														  NULL, NULL);
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

    if (testmode == true)
	{
        gtk_init (&argc, &argv);

        gCanvas.CreateFrameBuffer(width, height);
        Color color(0.0,0.0,1.0);
        gCanvas.DrawLineWithDDA(color, 2, 2, 200, 500);

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
    return 0;
}
