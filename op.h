/* See LICENSE file for copyright and license details. */

#ifndef OP_H
#define OP_H

#define OP_NAME_SIZE 16
#define OP_DESCR_SIZE 64

typedef enum {
    OP_N0,
    OP_N1,
    OP_N2,
} OpType; 

typedef struct {
    char name[OP_NAME_SIZE];
    OpType n;
    union {
        double (*op_n0)(void);
        double (*op_n1)(double);
        double (*op_n2)(double, double);
    };
    const char descr[OP_DESCR_SIZE];
} Op;

const Op *op(const char *name);

#endif
