/*
 * Copyright (C) 2015 2nd Foundation
 * All rights reserved
 */

#include <cairo.h>
#include <gtk/gtk.h>
#include <gdk/gdkkeysyms.h>
#include "os_layer.h"

gboolean on_expose_event (GtkWidget * widget, GdkEventExpose *event, gpointer data)
{
    printf("on_expose_event is called.\n");
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

gboolean on_key_press(GtkWidget *widget, GdkEventKey  *event, gpointer data)
{
    UIContext * pCurrentContext = (UIContext *)data;
    switch(event->keyval)
    {
        case GDK_Up:
            printf("Up\n");
            pCurrentContext->setKeyPressState(KEYPRESS_UP);
            break;
        case GDK_Left:
            pCurrentContext->setKeyPressState(KEYPRESS_LEFT);
            printf("Left\n");
            break;
        case GDK_Right:
            pCurrentContext->setKeyPressState(KEYPRESS_RIGHT);
            printf("Right\n");
            break;
        case GDK_Down:
            pCurrentContext->setKeyPressState(KEYPRESS_DOWN);
            printf("Down\n");
            break;
        case GDK_space:
            pCurrentContext->setKeyPressState(KEYPRESS_SPACE);
            printf("Space\n");
            break;
    }

    int key = event->keyval;
    printf("keyval = %d\n", key);
    return true;
}

void destroy(GtkWidget *widget, gpointer data)
{
    printf("GoodBye!\n");
    UIContext * pCurrentContext = (UIContext *)data;
    pCurrentContext->setQuitFlag();
    gtk_main_quit();
}

void UIContext::Init(int argc, char *argv[])
{
    gtk_init(&argc, &argv);
}

void UIContext::Prepare()
{
    GtkWidget *window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
    mPlatformWindow = window;
    g_signal_connect(window, "destroy", G_CALLBACK (destroy), this);
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
    gtk_widget_set_size_request(window, mWidth, mHeight);
    gtk_window_set_resizable(GTK_WINDOW(window), FALSE);

    g_signal_connect(window, "expose-event", G_CALLBACK(on_expose_event), this);
    g_signal_connect(window, "key-press-event", G_CALLBACK(on_key_press), this);
    gtk_widget_set_app_paintable(window, TRUE);
    gtk_widget_show_all(window);
}

void UIContext::InvalidateArea()
{
  if (mPlatformWindow == NULL)
      return;
  printf("Real invalidate.\n");
  gtk_widget_queue_draw((GtkWidget*)mPlatformWindow);
}

void UIContext::mainloop()
{
    gtk_main();
}
