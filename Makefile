# lc - line calculator
# See LICENSE file for copyright and license details.

.POSIX:

include config.mk

SRC = lc.c op.c stack.c utils.c
OBJ = $(SRC:.c=.o)

all: lc docs/lc.1

.c.o:
	$(CC) -c $< $(CFLAGS)

$(OBJ): config.mk op.h stack.h utils.h

lc: $(OBJ) 
	$(CC) -o $@ $(OBJ) $(LDFLAGS)

docs/lc.1: docs/lc.1.scd
	scdoc < $< > $@

clean:
	rm -f lc $(OBJ) docs/lc.1

.PHONY: all clean
