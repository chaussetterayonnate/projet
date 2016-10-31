## Simple SDL mini code

CC=gcc


CFLAGS= -Wall -Wextra -Werror -std=c99 -O3
LDFLAGS=
LDLIBS= -lm 

SRC= savingWheights.c xorPrototype.c 

OBJ= ${SRC:.c=.o}

all: savingWheights, xorPrototype

main: ${OBJ}

clean:
	rm -f *~ *.o
	rm -f xorPrototype
	rm -f savingWheights
	rm -f test.txt
# END
