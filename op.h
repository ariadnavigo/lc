/* See LICENSE file for copyright and license details. */

#ifndef OP_H
#define OP_H

#define OP_NAME_SIZE 16

typedef enum {
	OP_N0,
	OP_N1,
	OP_N2,
} OpType; 

typedef struct {
	char name[OP_NAME_SIZE];
	OpType n;
	union {
		long (*op_n0)(void);
		long (*op_n1)(long);
		long (*op_n2)(long, long);
	};
} Op;

const Op *op(const char *name);

#endif
