
SRCDIR=..

CC = g++
SRC = linux_gtk_layer.cpp \
      $(SRCDIR)/main.cpp \
	  $(SRCDIR)/math/Matrix2f.cpp \
      $(SRCDIR)/math/Matrix3f.cpp \
      $(SRCDIR)/math/Matrix4f.cpp \
      $(SRCDIR)/math/Quat4f.cpp \
      $(SRCDIR)/math/Vector2f.cpp \
      $(SRCDIR)/math/Vector3f.cpp \
      $(SRCDIR)/math/Vector4f.cpp \
	  $(SRCDIR)/Color.cpp \
	  $(SRCDIR)/RendererCanvas.cpp \
	  $(SRCDIR)/stdafx.cpp \
	  $(SRCDIR)/MeshObjectModel.cpp \
	  $(SRCDIR)/ModelLoader.cpp \
	  $(SRCDIR)/RenderDevice.cpp \
	  $(SRCDIR)/Transform.cpp

TARGET = SmartRasterizer
CFLAGS = -D__DEBUG -DUSE_GTK -g `pkg-config --cflags --libs gtk+-2.0`
CFLAGS += -I../
CFLAGS += -I../include/
CFLAGS += -I../include/math/
CFLAGS += -I/usr/include/

$(TARGET): $(SRC)
	$(CC) $(SRC) -o $(TARGET) $(CFLAGS)
.PHONY clean:
	rm $(TARGET) -rf
