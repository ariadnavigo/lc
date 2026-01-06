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

typedef enum {
    DEF_MODE,
    DOCS_MODE,
    EXPR_MODE
} LCMode;

static void usage(void);
static const char *error_str(void);
static void pprint_op(const Op *op_ptr);

static int apply_op(double *dest, const Op *op_ptr);
static int parse(const char *prompt);

static int docs_single_op(const char *name);
static void docs_all_ops(void);

static LCErr lc_err = NO_ERROR;

static void usage(void) {
    die("usage: lc [-Dv] [-d OPERATION] [-e EXPRESSION]");
}

static const char *error_str(void) {
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

static void pprint_op(const Op *op_ptr) {
    switch (op_ptr->n) {
    case 0:
        printf("\t");
        break;
    case 1:
        printf("n1\t");
        break;
    case 2:
        printf("n1 n2\t");
        break;
    default:
        break; // UNREACHABLE
    }

    printf("%s\t%s\n", op_ptr->name, op_ptr->descr);
}

static int apply_op(double *dest, const Op *op_ptr) {
    double arg1, arg2;

    switch (op_ptr->n) {
    case OP_N0:
        *dest = (*op_ptr->op_n0)();
        break;
    case OP_N1:
        if (stack_pop(&arg1, NULL) < 0)
            return -1;
        *dest = (*op_ptr->op_n1)(arg1);
        break;
    case OP_N2:
        if (stack_pop(&arg1, &arg2, NULL) < 0)
            return -1;
        *dest = (*op_ptr->op_n2)(arg2, arg1); // args are inverted!
        break;
    default:
        break; // Theoretically unreachable
    }

    return 0;
}

static int parse(const char *prompt) {
    double num_buf, res;
    const Op *op_ptr;
    char *tok, *str, *endptr;
    char cpy[PROMPT_SIZE];

    strncpy(cpy, prompt, PROMPT_SIZE);
    str = cpy;
    while ((tok = strtok(str, " ")) != NULL) {
        str = NULL; // Required by strtok()

        /* If token is a number */
        num_buf = strtod(tok, &endptr);
        if (endptr[0] != '\0') 
            goto parse_op;

        if (stack_push(num_buf) < 0) {
            lc_err = ERR_STACK_OVER;
            return -1;
        } else {
            /* 
             * If we arrived here, it's a number that was 
             * succesfully pushed to the stack, so let's not run
             * through the rest of the while loop.
             */
            continue;
        }

parse_op:
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

static int docs_single_op(const char *name) {
    const Op *op_ptr;

    if ((op_ptr = op(name)) == NULL) {
        lc_err = ERR_OP;
        return -1;
    }

    pprint_op(op_ptr);

    return 0;
}

static void docs_all_ops(void) {
    const Op *op_ptr;
    
    for (op_ptr = op_iter(1); op_ptr != NULL; op_ptr = op_iter(0))
        pprint_op(op_ptr);
}

int main(int argc, char *argv[]) {
    int opt;
    LCMode mode;
    size_t prompt_lastchar;
    char prompt[PROMPT_SIZE];

    mode = DEF_MODE;
    while ((opt = getopt(argc, argv, ":Dd:e:v")) != -1) {
        switch (opt) {
        case 'D':
            mode = DOCS_MODE;
            docs_all_ops();
            break;
        case 'd':
            mode = DOCS_MODE;
            docs_single_op(optarg);
            break;
        case 'e':
            mode = EXPR_MODE;
            strncpy(prompt, optarg, PROMPT_SIZE);
            break;
        case 'v':
            /* Ignore mode */
            printf("lc %s\n", VERSION);
            return 0;
        default:
            usage();
            break; // UNREACHABLE
        }
    }

    /* 
     * This is why we break from DOCS_MODE cases above, instead of using
     * immediate returns.
     */
    if (lc_err != NO_ERROR)
        die(error_str());

    switch (mode) {
    case DOCS_MODE:
        return 0;
    case DEF_MODE:
        fgets(prompt, PROMPT_SIZE, stdin);
        break;
    default: // i.e. EXPR_MODE
        break;
    }

    prompt_lastchar = strlen(prompt) - 1; 
    if (prompt[prompt_lastchar] == '\n')
        prompt[prompt_lastchar] = '\0';

    if (parse(prompt) < 0)
        die(error_str());

    printf("%f\n", stack[sp]);

    return 0;

}
