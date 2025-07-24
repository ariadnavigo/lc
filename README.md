# lc - Line-based RPN calculator

lc is a line-based RPN calculator that takes input from standard input. It
supports floating point arithmetics and aims to be portable and standards
compliant across POSIX(-like) systems.

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
4. [scdoc][scdoc-git]: to generate the manpage.

You may edit ``config.mk`` to tweak compiling options to your needs.

You may install lc by invoking ``make install`` with the proper permissions. You
may set ``DESTDIR`` to set up a destination directory, typically used to create
distibution packages. Conversely, you may uninstall lc by invoking ``make
uninstall`` (passing DESTDIR if necessary as well).

## Usage

lc accepts valid RPN expressions (e.g. ``3 4 +``, for "3 + 4") from
standard input. The result is printed to standard output in its own line. Error
and warning messages are printed to standard error.

For example:

```
$ echo '2 4 +' | lc
6.000000
```

Passing the ``-v`` option will print lc's version number and exit.

## License

lc is licensed under the MIT License. See LICENSE file for copyright and
license details.

[scdoc-git]: https://git.sr.ht/~sircmpwn/scdoc
