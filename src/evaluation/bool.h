#ifndef BOOL_H
#define BOOL_H

#include "../parsing/parsing.h"

bool bool_eq(expression left, expression right);
bool bool_neq(expression left, expression right);
bool bool_geq(expression left, expression right);
bool bool_gt(expression left, expression right);
bool bool_leq(expression left, expression right);
bool bool_lt(expression left, expression right);

#endif
