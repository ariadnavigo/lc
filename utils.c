/* See LICENSE file for copyright and license details. */

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

#include "utils.h"

void 
die(const char *fmt, ...)
{
	va_list ap;

	va_start(ap, fmt);
	vfprintf(stderr, fmt, ap);
	va_end(ap);

	fputc('\n', stderr);

	exit(1);
}

void 
usage(void)
{
	die("usage: lc [-v] [PROMPT]");
}
