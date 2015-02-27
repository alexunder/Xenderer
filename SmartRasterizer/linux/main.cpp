/*
 * Copyright (C) 2015 2nd Foundation
 * All rights reserved
 */

#include <cairo.h>	// 绘图所需要的头文件
#include <gtk/gtk.h>
#include "stdafx.h"
#include "RendererCanvas.h"

int gWidth = 800;
int gHeight = 600;
RendererCanvas gCanvas;

gboolean on_expose_event (GtkWidget * widget, GdkEventExpose *event, gpointer data)
{
	cairo_t *cr = gdk_cairo_create(widget->window);	// 创建cairo环境，注意参数

	GdkPixbuf * pixframebuffer = gdk_pixbuf_new_from_data((const unsigned char*)gCanvas.getframeBuffer(), 
														  GDK_COLORSPACE_RGB, 
														  TRUE, 
														  8, 
														  gWidth,
														  gHeight,
														  gWidth*4,
														  NULL, NULL);
	// 画背景图
	// 获取图片
	//GdkPixbuf *src_pixbuf = gdk_pixbuf_new_from_file("./image/back.jpg", NULL); 
	// 指定图片大小
	//GdkPixbuf* dst_pixbuf = gdk_pixbuf_scale_simple(src_pixbuf, gWidth, gHeight, GDK_INTERP_BILINEAR);
	
	// dst_pixbuf作为cr环境的画图原材料，(0, 0)：画图的起点坐标
	gdk_cairo_set_source_pixbuf(cr, pixframebuffer, 0, 0);
	cairo_paint(cr);	// 绘图
	
	// 释放资源
	//g_object_unref(dst_pixbuf);
	//g_object_unref(src_pixbuf);
	g_object_unref(pixframebuffer);

	/*
	// 绘图与写字共存的测试
	// 如果绘完图片后想继续写字或画线，
	// 必须手动设置画笔颜色cairo_set_source_rgb()
	// 否则，字体或线条会被图片覆盖。
	cairo_set_source_rgb(cr, 0.627, 0, 0);  // 设置字体颜色
	cairo_set_font_size(cr, 40.0);			// 设置字体大小
	cairo_move_to(cr, 50.0, 130.0);			// 写字的起点坐标
	cairo_show_text(cr, "This is a test");	// 写字
	*/

	cairo_destroy(cr);	// 回收所有Cairo环境所占用的内存资源

	return FALSE;	// 必须返回FALSE
}

int main (int argc, char *argv[])
{
	gtk_init (&argc, &argv);

	//test the buffer
	//pFrameBuffer =(unsigned int*)malloc(gWidth*gHeight*sizeof(unsigned int));
	//memset(pFrameBuffer, 0, gWidth*gHeight*sizeof(unsigned int) );

	
    gCanvas.CreateFrameBuffer(gWidth, gHeight);
    Color color(0.0,0.0,1.0);
    gCanvas.DrawLine(color, 2, 2, 200, 500);

	GtkWidget *window = gtk_window_new (GTK_WINDOW_TOPLEVEL); // 顶层窗口
	g_signal_connect(window, "destroy", G_CALLBACK (gtk_main_quit), NULL);
	gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);	// 中央位置显示
	gtk_widget_set_size_request(window, gWidth, gHeight);		    // 窗口最小大小
	gtk_window_set_resizable(GTK_WINDOW(window), FALSE);	// 固定窗口的大小


	// 绘图事件信号与回调函数的连接
	g_signal_connect(window, "expose-event", G_CALLBACK(on_expose_event), NULL);

	gtk_widget_set_app_paintable(window, TRUE);	// 允许窗口可以绘图

	gtk_widget_show_all(window);	// 显示所有控件

	gtk_main();
}
