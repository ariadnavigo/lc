LC(1)

# NAME

lc - line-based RPN calculator

# SYNOPSIS

*lc* [*-v*]

# DESCRIPTION

lc is a line-based RPN calculator that takes input from standard input. It
supports floating point arithmetics and aims to be portable and standards
compliant across POSIX(-like) systems.

lc accepts valid RPN expressions (e.g. "3 4 +", for "3 + 4") from
standard input. The result is printed to standard output in its own line. Error
and warning messages are printed to standard error.

Passing the _-v_ option will print lc's version number and exit.

# OPTIONS

*-v*
	Print lc's version number and exit.


# EXIT STATUS

lc returns 0 as its exit status if successful and >0 in case of an error.  

# EXAMPLES

Getting the result of "2 + 4" and printing the result to standard output:

$ *echo '2 4 +' | lc*++
6.000000

Getting the result of "(sqrt(4) - 3) / 3" and printing the result:

$ *echo '4 sqrt 3 - 3 /' | lc*++
-0.333333

# SEE ALSO

*bc*(1), *dc*(1)
