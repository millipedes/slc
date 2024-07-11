#include "string.h"

char * string_addition(expression left, expression right) {
  size_t left_len = strnlen(left.value.string_value, MAX_STR);
  size_t right_len = strnlen(right.value.string_value, MAX_STR);
  char * result = (char *)calloc(left_len + right_len + 1, sizeof(char));
  strncpy(result, left.value.string_value, left_len);
  strncpy(result + left_len, right.value.string_value, left_len + 1);
  return result;
}

bool string_eq(expression left, expression right) {
  size_t left_len = strnlen(left.value.string_value, MAX_STR);
  if(left_len != strnlen(left.value.string_value, MAX_STR))
    return false;
  return !strncmp(left.value.string_value, right.value.string_value, left_len);
}
