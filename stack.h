/* See LICENSE file for copyright and license details. */

#ifndef STACK_H
#define STACK_H

#define STACK_SIZE 32 /* Elements max allowed in stack */

extern double stack[STACK_SIZE];
extern int sp; /* Our "stack pointer" */

int stack_push(double item);
int stack_pop(double *dest, ...);

#endif
