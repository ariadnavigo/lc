# lc version
VERSION = 0.1.0

# Paths
# DESTDIR is supported to ease packaging. If you're setting DESTDIR, please do
# so *with* a trailing /

PREFIX = /usr/local
MANPREFIX = /usr/local/man

# Flags
CPPFLAGS = -D_POSIX_C_SOURCE=202405L -DVERSION=\"$(VERSION)\"
CFLAGS = -std=c17 -Wall -Wextra -pedantic $(CPPFLAGS)
LDFLAGS = -lm

# Compiler and linker
CC = cc
