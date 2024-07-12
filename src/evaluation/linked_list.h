#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include "evaluation_types.h"

typedef struct SLC_VALUE_LL_T {
  char * name;
  slc_value value;
  struct SLC_VALUE_LL_T * next;
} slc_value_ll;

slc_value_ll init_slc_value_ll(const char * name, slc_value the_slc_value);
slc_value slc_value_in_list(slc_value_ll the_slc_value_ll, const char * name);
slc_value_ll update_slc_value_ll(slc_value_ll head, slc_value_ll tail);
void free_slc_value_ll(slc_value_ll the_slc_value_ll);

#endif
