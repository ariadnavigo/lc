# lc - line calculator
# See LICENSE file for copyright and license details.

.POSIX:

# lc version
VERSION = v0.3.0

# Paths
# DESTDIR is supported to ease packaging. If you're setting DESTDIR, please do
# so *with* a trailing /

PREFIX = /usr/local
MANPREFIX = /usr/local/man

# Flags
CPPFLAGS = -D_POSIX_C_SOURCE=202405L -DVERSION=\"$(VERSION)\"
CFLAGS = -std=c23 -Wall -Wextra -pedantic $(CPPFLAGS)
LDFLAGS = -lm

# Compiler and linker
CC = cc

SRC = lc.c op.c stack.c
OBJ = $(SRC:.c=.o)

all: lc docs/lc.1

.c.o:
	$(CC) -c $< $(CFLAGS)

$(OBJ): op.h stack.h

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
