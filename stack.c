/* See LICENSE file for copyright and license details. */

#include <stdarg.h>
#include <stddef.h>

#include "stack.h"

double stack[STACK_SIZE];
int sp = -1;

int 
stack_push(double item)
{
	if (sp + 1 >= STACK_SIZE) {
		sp = STACK_SIZE - 1;
		return -1;
	}

	stack[++sp] = item;
	
	return 0;
}

int
stack_pop(double *dest, ...)
{
	va_list ap;
	double *ptr;
	int ret;

	ret = 0;
	va_start(ap, dest);

	for (ptr = dest; ptr != NULL; ptr = va_arg(ap, double *)) {
		if (sp <= -1) {
			sp = -1;
			ret = -1;
			goto exit;
		}

		*ptr = stack[sp--];
	}

exit:
	va_end(ap);
	return ret;
}
