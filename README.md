# lc - Line-based RPN calculator

lc is a line-based RPN calculator that takes input either from the command line
or standard input. It supports floating point arithmetics and aims to be
portable and standards compliant across POSIX(-like) systems.

## Caveats

This project is in a **very early stage** of development. Many basic 
mathematical operations are missing. Error checking is still in development.
POSIX portability and compatibility with non-GNU libraries have **not** been
tested outside Linux yet.

In these early stages, interfaces may quickly change and documentation may not
perfectly reflect those changes immediately.

## Build

In order to build lc, you will need:

1. A Linux system
2. A C17 compiler (gcc, tcc, clang are supported, as well as linking against the
   MUSL implementation of the C Standard Library)
3. ``make(1)`` (GNU make, bmake are supported)

You may edit ``config.mk`` to tweak compiling options to your needs.

## Usage

The command-line interface for lc is described below:

```
$ lc [-v] [PROMPT]
```

lc accepts valid RPN expressions (e.g. ``3 4 +``, for "3 + 4") either from
standard input or as its optional ``PROMPT`` command-line parameter (enclosed by
quotes). The result is printed to standard output in its own line. Error and
warning messages are printed to standard error.

For example:

```
$ ./lc '2 4 +'
6.000000
```

## License

lc is licensed under the MIT License. See LICENSE file for copyright and
license details.
