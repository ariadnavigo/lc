/* See LICENSE file for copyright and license details. */

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
stack_pop(double *dest)
{
	if (sp <= -1) {
		sp = -1;
		return -1;
	}

	*dest = stack[sp--];

	return 0;
}
