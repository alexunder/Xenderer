/*
 * Copyright (C) 2015 2nd Foundation
 * All rights reserved
 */

#include <cairo.h>
#include <gtk/gtk.h>
#include "stdafx.h"
#include "RendererCanvas.h"

int gWidth = 800;
int gHeight = 600;
RendererCanvas gCanvas;

gboolean on_expose_event (GtkWidget * widget, GdkEventExpose *event, gpointer data)
{
	cairo_t *cr = gdk_cairo_create(widget->window);

	GdkPixbuf * pixframebuffer = gdk_pixbuf_new_from_data((const unsigned char*)gCanvas.getframeBuffer(), 
														  GDK_COLORSPACE_RGB, 
														  TRUE, 
														  8, 
														  gWidth,
														  gHeight,
														  gWidth*4,
														  NULL, NULL);
	
	gdk_cairo_set_source_pixbuf(cr, pixframebuffer, 0, 0);
	cairo_paint(cr);
	
	g_object_unref(pixframebuffer);


	cairo_destroy(cr);

	return FALSE;
}

int main (int argc, char *argv[])
{
	gtk_init (&argc, &argv);

    gCanvas.CreateFrameBuffer(gWidth, gHeight);
    Color color(0.0,0.0,1.0);
    gCanvas.DrawLineWithDDA(color, 2, 2, 200, 500);

	GtkWidget *window = gtk_window_new (GTK_WINDOW_TOPLEVEL); // 顶层窗口
	g_signal_connect(window, "destroy", G_CALLBACK (gtk_main_quit), NULL);
	gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);	// 中央位置显示
	gtk_widget_set_size_request(window, gWidth, gHeight);		    // 窗口最小大小
	gtk_window_set_resizable(GTK_WINDOW(window), FALSE);	// 固定窗口的大小


	g_signal_connect(window, "expose-event", G_CALLBACK(on_expose_event), NULL);

	gtk_widget_set_app_paintable(window, TRUE);	// 允许窗口可以绘图

	gtk_widget_show_all(window);	// 显示所有控件

	gtk_main();
}
