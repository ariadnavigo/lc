/* See LICENSE file for copyright and license details. */

#include <math.h>
#include <string.h>

#include "op.h"

static double op_add(double m, double n);
static double op_subst(double m, double n);
static double op_mult(double m, double n);
static double op_div(double m, double n);
static double op_mod(double m, double n);
static double op_root(double m, double n);

const Op op_list[] = {
	{ "+", OP_N2, { .op_n2 = op_add } },
	{ "-", OP_N2, { .op_n2 = op_subst } },
	{ "*", OP_N2, { .op_n2 = op_mult } },
	{ "/", OP_N2, { .op_n2 = op_div } },
	{ "mod", OP_N2, { .op_n2 = op_mod } },
	{ "^", OP_N2, { .op_n2 = pow } }, /* libm */
	{ "root", OP_N2, { .op_n2 = op_root } },
	{ "log", OP_N1, { .op_n1 = log } }, /* libm */
	{ "log10", OP_N1, { .op_n1 = log10 } }, /* libm */
	{ "sin", OP_N1, { .op_n1 = sin } }, /* libm */
	{ "cos", OP_N1, { .op_n1 = cos } }, /* libm */
	{ "tan", OP_N1, { .op_n1 = tan } }, /* libm */
	{ "asin", OP_N1, { .op_n1 = tan } }, /* libm */
	{ "acos", OP_N1, { .op_n1 = tan } }, /* libm */
	{ "atan", OP_N1, { .op_n1 = tan } }, /* libm */
	{ "", OP_N0, { .op_n0 = NULL } }
};

static double
op_add(double m, double n)
{
	return m + n;
}

static double
op_subst(double m, double n)
{
	return m - n;
}

static double
op_mult(double m, double n)
{
	return m * n;
}

static double
op_div(double m, double n)
{
	return m / n;
}

static double
op_mod(double m, double n)
{
	return (double)((long)m % (long)n);
}

static double
op_root(double m, double n)
{
	return pow(m, 1 / n);
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
