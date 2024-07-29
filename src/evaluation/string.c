#include "string.h"

bool string_eq(expression left, expression right) {
  size_t left_len = strnlen(left.value.string_value, MAX_STR);
  if(left_len != strnlen(left.value.string_value, MAX_STR))
    return false;
  size_t result = !strncmp(left.value.string_value, right.value.string_value, left_len);
  return result;
}

bool string_neq(expression left, expression right) {
  return !string_eq(left, right);
}
