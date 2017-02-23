/*
 * Copyright (C) 2015 2nd Foundation
 * All rights reserved
 */

#include <cairo.h>
#include <gtk/gtk.h>
#include "os_layer.h"

gboolean on_expose_event (GtkWidget * widget, GdkEventExpose *event, 
                          gpointer data) {
    UIContext * pCurrentContext = (UIContext *)data;
	cairo_t *cr = gdk_cairo_create(widget->window);
	GdkPixbuf * pixframebuffer = gdk_pixbuf_new_from_data(
        (const unsigned char*)pCurrentContext->getFB(),
		GDK_COLORSPACE_RGB, TRUE, 8,
        pCurrentContext->getWidth(),
        pCurrentContext->getHeight(),
        pCurrentContext->getWidth()*4,
        NULL, NULL);
	gdk_cairo_set_source_pixbuf(cr, pixframebuffer, 0, 0);
	cairo_paint(cr);
	g_object_unref(pixframebuffer);

	cairo_destroy(cr);
	return FALSE;
}

void UIContext::Init(int argc, char *argv[]) {
    gtk_init(&argc, &argv);
}

void UIContext::Prepare() {
    GtkWidget *window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
    g_signal_connect(window, "destroy", G_CALLBACK (gtk_main_quit), NULL);
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
    gtk_widget_set_size_request(window, mWidth, mHeight);
    gtk_window_set_resizable(GTK_WINDOW(window), FALSE);

    g_signal_connect(window, "expose-event", G_CALLBACK(on_expose_event), this);
    gtk_widget_set_app_paintable(window, TRUE);
    gtk_widget_show_all(window);
    gtk_main();
}
