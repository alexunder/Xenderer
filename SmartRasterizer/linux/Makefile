
SRCDIR=..

CC = g++
SRC = main.cpp \
	  $(SRCDIR)/Color.cpp \
	  $(SRCDIR)/RendererCanvas.cpp \
	  $(SRCDIR)/stdafx.cpp \

TARGET = SmartRasterizer
CFLAGS = `pkg-config --cflags --libs gtk+-2.0`
CFLAGS += -I ../

$(TARGET): $(SRC)
	$(CC) $(SRC) -o $(TARGET) $(CFLAGS)
.PHONY clean:
	rm $(TARGET) -rf
