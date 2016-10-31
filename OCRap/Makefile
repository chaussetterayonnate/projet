## Simple SDL mini code

CC=gcc

CPPFLAGS= `pkg-config --cflags sdl`
CFLAGS= -Wall -Wextra -Werror -std=c99 -O3
LDFLAGS=
LDLIBS= `pkg-config --libs sdl` -lSDL_image -lm

SRC= load.c ocr_decoupage.c greyscale.c savingWheights.c xorPrototype.c 

OBJ= ${SRC:.c=.o}

all: load, ocr_decoupage, greyscale, savingWheights, xorPrototype

main: ${OBJ}

clean:
	rm -f *~ *.o
	rm -f load
	rm -f greyscale
	rm -f ocr_decoupage
	rm -f xorPrototype
	rm -f savingWheights
	rm -f test.txt
# END
