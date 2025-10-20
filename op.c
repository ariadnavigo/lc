/* See LICENSE file for copyright and license details. */

#include <math.h>
#include <string.h>

#include "op.h"

static double op_const_pi(void);
static double op_const_e(void);

static double op_add(double m, double n);
static double op_subst(double m, double n);
static double op_mult(double m, double n);
static double op_div(double m, double n);
static double op_mod(double m, double n);
static double op_root(double m, double n);
static double op_rad(double m);
static double op_deg(double m);

const Op op_list[] = {
    { "pi", OP_N0, { .op_n0 = op_const_pi }, "Pi constant" },
    { "e", OP_N0, { .op_n0 = op_const_e }, "Euler's constant" },
    { "+", OP_N2, { .op_n2 = op_add }, "Addition" },
    { "-", OP_N2, { .op_n2 = op_subst }, "Substraction" },
    { "*", OP_N2, { .op_n2 = op_mult }, "Multiplication" },
    { "/", OP_N2, { .op_n2 = op_div }, "Division" },
    { "mod", OP_N2, { .op_n2 = op_mod }, "Modulo" },
    { "^", OP_N2, { .op_n2 = pow }, "" }, /* libm */
    { "root", OP_N2, { .op_n2 = op_root }, "" },
    { "log", OP_N1, { .op_n1 = log }, "Natural logarithm" }, /* libm */
    { "log10", OP_N1, { .op_n1 = log10 }, "Logarithm base 10" }, /* libm */
    { "deg2rad", OP_N1, { .op_n1 = op_rad }, "Convert degrees into radians" },
    { "rad2deg", OP_N1, { .op_n1 = op_deg }, "Convert radians into degrees" },
    { "sin", OP_N1, { .op_n1 = sin }, "Sine" }, /* libm */
    { "cos", OP_N1, { .op_n1 = cos }, "Cosine" }, /* libm */
    { "tan", OP_N1, { .op_n1 = tan }, "Tangent" }, /* libm */
    { "asin", OP_N1, { .op_n1 = asin }, "Arcsine" }, /* libm */
    { "acos", OP_N1, { .op_n1 = acos }, "Arccosine" }, /* libm */
    { "atan", OP_N1, { .op_n1 = atan }, "Arctangent" }, /* libm */
    { "", OP_N0, { .op_n0 = NULL }, "" } /* "NULL"-terminator */
};

static double op_const_pi(void)
{
    return atan(1) * 4;
}

static double op_const_e(void)
{
    return exp(1);
}

static double op_add(double m, double n)
{
    return m + n;
}

static double op_subst(double m, double n)
{
    return m - n;
}

static double op_mult(double m, double n)
{
    return m * n;
}

static double op_div(double m, double n)
{
    return m / n;
}

static double op_mod(double m, double n)
{
    return (double)((long)m % (long)n);
}

static double op_root(double m, double n)
{
    return pow(m, 1 / n);
}

static double op_rad(double m)
{
    return m * op_const_pi() / 180;
}

static double op_deg(double m)
{
    return m * 180 / op_const_pi();
}

const Op *op(const char *name)
{
    const Op *ptr;

    for (ptr = op_list; strncmp(ptr->name, "", OP_NAME_SIZE) != 0; ++ptr) {
        if (strncmp(ptr->name, name, OP_NAME_SIZE) == 0)
            return ptr;
    }

    return NULL;
}
