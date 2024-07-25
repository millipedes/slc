#ifndef STRING_H
#define STRING_H

#include "../parsing/parsing.h"

char * string_addition(expression left, expression right);
bool string_eq(expression left, expression right);
bool string_neq(expression left, expression right);

#endif
