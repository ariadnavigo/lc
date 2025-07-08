/* See LICENSE file for copyright and license details. */

#include <string.h>

#include "op.h"

static double op_add(double m, double n);

const Op op_list[] = {
	{ "+", OP_N2, { .op_n2 = op_add } },
	{ "", OP_N0, { .op_n0 = NULL } }
};

static double
op_add(double m, double n)
{
	return m + n;
}

const Op *
op(const char *name)
{
	const Op *ptr;

	for (ptr = op_list; strncmp(ptr->name, "", OP_NAME_SIZE) != 0; ++ptr) {
		if (strncmp(ptr->name, name, OP_NAME_SIZE) == 0)
			return ptr;
	}

	return NULL;
}
