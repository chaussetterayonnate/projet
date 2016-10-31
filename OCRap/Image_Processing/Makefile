## Simple SDL mini code

CC=gcc

CPPFLAGS= `pkg-config --cflags sdl`
CFLAGS= -Wall -Wextra -Werror -std=c99 -O3
LDFLAGS=
LDLIBS= `pkg-config --libs sdl` -lSDL_image

SRC=  load.c ocr_decoupage.c greyscale.c

OBJ= ${SRC:.c=.o}

all:  load, ocr_decoupage, greyscale

main: ${OBJ}

clean:
	rm -f *~ *.o
	rm -f load
	rm -f greyscale
	rm -f ocr_decoupage
# END
