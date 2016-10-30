## Simple SDL mini code

CC=gcc

CPPFLAGS= `pkg-config --cflags sdl`
CFLAGS= -Wall -Wextra -Werror -std=c99 -O3
LDFLAGS=
LDLIBS= `pkg-config --libs sdl` -lSDL_image

SRC= load.c greyscale.c
OBJ= ${SRC:.c=.o}

all: load, greyscale

main: ${OBJ}

clean:
	rm -f *~ *.o
	rm -f load
	rm -f greyscale	
# END
