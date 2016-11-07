
SRCDIR=.

CC = gcc
SRC = $(SRCDIR)/mini3d.c

TARGET = mini3d
CFLAGS = -lm
CFLAGS = -g `pkg-config --cflags --libs gtk+-2.0`
LIBS =-L/usr/lib/x86_64-linux-gnu -lm

$(TARGET): $(SRC)
	$(CC) $(SRC) -o $(TARGET) $(CFLAGS) $(LIBS)
.PHONY clean:
	rm $(TARGET) -rf
