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
	scdoc < docs/lc.1.scd > $@

clean:
	rm -f lc $(OBJ) docs/lc.1

install: all
	mkdir -p $(DESTDIR)$(PREFIX)/bin
	cp -f lc $(DESTDIR)$(PREFIX)/bin
	chmod 755 $(DESTDIR)$(PREFIX)/bin/lc
	mkdir -p $(DESTDIR)$(MANPREFIX)/man1
	cp -f docs/lc.1 $(DESTDIR)$(MANPREFIX)/man1
	chmod 644 $(DESTDIR)$(MANPREFIX)/man1/lc.1

uninstall:
	rm -f $(DESTDIR)$(PREFIX)/bin/lc
	rm -f $(DESTDIR)$(MANPREFIX)/man1/lc.1

.PHONY: all clean install uninstall
