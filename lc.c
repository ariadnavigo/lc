/* See LICENSE file for copyright and license details. */

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "op.h"
#include "stack.h"
#include "utils.h"

#define PROMPT_SIZE 128

typedef enum {
	NO_ERROR,
	ERR_FEW_ARGS,
	ERR_OP,
	ERR_STACK_OVER
} LCErr;

static const char *error_str(void);
static int apply_op(double *dest, const Op *op_ptr);
static int parse(const char *prompt);

static LCErr lc_err = NO_ERROR;

static const char *
error_str(void)
{
	switch (lc_err) {
	case ERR_FEW_ARGS:
		return "Too few arguments available for an operation";
	case ERR_OP:
		return "Invalid operator";
	case ERR_STACK_OVER:
		return "Calculator stack overflow";
	default:
		return "";
	}
}

static int
apply_op(double *dest, const Op *op_ptr)
{
	double arg1, arg2;

	switch (op_ptr->n) {
	case OP_N1:
		if (stack_pop(&arg1) < 0)
			return -1;
		*dest = (*op_ptr->op_n1)(arg1);
		break;
	case OP_N2:
		if (stack_pop(&arg1) < 0 || stack_pop(&arg2) < 0)
			return -1;
		*dest = (*op_ptr->op_n2)(arg1, arg2);
		break;
	default:
		break; /* Theoretically unreachable */
	}

	return 0;
}

static int
parse(const char *prompt)
{
	double num_buf, res;
	const Op *op_ptr;
	char *tok, *str, *endptr;
	char cpy[PROMPT_SIZE];

	strncpy(cpy, prompt, PROMPT_SIZE);
	str = cpy;
	while ((tok = strtok(str, " ")) != NULL) {
		str = NULL; /* Required by strtok() */

		/* If token is a number */
		num_buf = strtod(tok, &endptr);
		if (endptr[0] == '\0') {
			/* TODO: Check for overflow. */
			stack_push(num_buf);
			continue; /* This saves us an else clause */
		} 

		/* Non-numbers are treated as ops. */
		
		if ((op_ptr = op(tok)) == NULL) {
			lc_err = ERR_OP;
			return -1;
		}

		if ((apply_op(&res, op_ptr)) < 0) {
			lc_err = ERR_FEW_ARGS;
			return -1;
		}

		if (stack_push(res) < 0) {
			lc_err = ERR_STACK_OVER;
			return -1;
		}
	}
	
	return 0;
}

int 
main(int argc, char *argv[])
{
	int opt;
	size_t prompt_lastchar;
	char prompt[PROMPT_SIZE];

	while ((opt = getopt(argc, argv, ":vh")) != -1) {
		switch (opt) {
		case 'v':
			printf("lc %s\n", VERSION);
			return 0;
		default:
			usage();
			break; /* UNREACHABLE */
		}
	}

	if (optind >= argc) {
		fgets(prompt, PROMPT_SIZE, stdin);
		prompt_lastchar = strlen(prompt) - 1; 
		if (prompt[prompt_lastchar] == '\n')
			prompt[prompt_lastchar] = '\0';
	} else {
		snprintf(prompt, PROMPT_SIZE, "%s", argv[optind]);
	}

	if (parse(prompt) < 0)
		die(error_str());

	printf("%f\n", stack[sp]);

	return 0;

}
