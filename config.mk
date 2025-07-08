# lc version
VERSION = 0.0.0

# Flags
CPPFLAGS = -D_POSIX_C_SOURCE=202405L -DVERSION=\"$(VERSION)\"
CFLAGS = -std=c17 -Wall -Wextra -pedantic $(CPPFLAGS)

# Compiler and linker
CC = cc
