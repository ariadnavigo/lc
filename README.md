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
2. A C23 compiler (gcc, tcc, clang are supported, as well as linking against the
   MUSL implementation of the C Standard Library)
3. ``make(1)`` (GNU make, bmake are supported)
4. [scdoc][scdoc-git]: to generate the manpage.

You may edit ``config.mk`` to tweak compiling options to your needs.

You may install lc by invoking ``make install`` with the proper permissions. You
may set ``DESTDIR`` to set up a destination directory, typically used to create
distibution packages. Conversely, you may uninstall lc by invoking ``make
uninstall`` (passing DESTDIR if necessary as well).

## Usage

lc accepts valid RPN expressions (e.g. ``3 4 +``, for "3 + 4") from standard
input by default or by passing the ``-e`` option. The result is printed to
standard output in its own line. Error o and warning messages are printed to
standard error.

For example:

```shell
$ echo '2 4 +' | lc
6.000000
$ lc -e '-10 3 ^'
-1000.000000
```

A manual page ``lc(1)`` is provided with further information about other
options and lc in general.

## Contributing

Patches and discussion are welcome at the [lc-devel mailing list][lc-devel-ml].
If you are not familiar with the Git email patch workflow,
[git-send-email.io][git-mail-web] is a great resource that walks you through the
basics. 

When sending a patch for the first time, it is highly recommended to set up the
email address like this:

```shell
$ git config sendemail.to "~ariadna/lc-devel@lists.sr.ht"
```

The first version of a patch should be marked using ``-v1``:

```shell
$ git send-email --anotate -v1 HEAD^
```

For further versions of the patch, change ``-v1`` to ``-v2, -v3, ...`` as
required.

Subscribe to the [lc-announce mailing list][lc-announce-ml] for announcements 
about releases and other critical milestones.

Tickets are tracked at the [lc tracker][lc-tracker].

You may find further information about this project at the [lc project
hub][lc-hub] as well.

## License

lc is licensed under the MIT License. See LICENSE file for copyright and
license details.

[scdoc-git]: https://git.sr.ht/~sircmpwn/scdoc

[lc-devel-ml]: https://lists.sr.ht/~ariadna/lc-devel

[git-mail-web]: https://git-send-email.io/

[lc-announce-ml]: https://lists.sr.ht/~ariadna/lc-announce

[lc-tracker]: https://todo.sr.ht/~ariadna/lc

[lc-hub]: https://sr.ht/~ariadna/lc
