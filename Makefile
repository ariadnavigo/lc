# lc - line calculator
# See LICENSE file for copyright and license details.

.POSIX:

include config.mk

SRC = lc.c op.c stack.c utils.c
OBJ = $(SRC:.c=.o)

all: lc

.c.o:
	$(CC) -c $< $(CFLAGS)

$(OBJ): config.mk op.h stack.h utils.h

lc: $(OBJ) 
	$(CC) -o $@ $(OBJ)

clean:
	rm -f lc $(OBJ)

.PHONY: all clean
