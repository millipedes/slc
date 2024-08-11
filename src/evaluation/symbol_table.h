#ifndef SYM_TAB_H
#define SYM_TAB_H

#include "evaluation_types.h"

#define DJB2_HASH_VALUE    5381
#define DJB2_HASH_MULTIPLE 33

#define QTY_BUCKETS 37

size_t djb2_hash(const char * value);

typedef struct SLC_VALUE_LL_T {
  char * name;
  slc_value value;
  struct SLC_VALUE_LL_T * next;
} slc_value_ll;

typedef struct SYMBOL_TABLE_T {
  slc_value_ll values[QTY_BUCKETS];
} symbol_table;

slc_value_ll init_slc_value_ll(const char * name, slc_value the_slc_value);
slc_value slc_value_in_list(slc_value_ll the_slc_value_ll, const expression the_expr, const symbol_table st);
slc_value get_value_from_array(slc_value value, const expression the_expr, symbol_table st, int i_deep);
slc_value_ll update_slc_value_ll(slc_value_ll head, slc_value_ll tail);
void free_slc_value_ll(slc_value_ll the_slc_value_ll);

symbol_table init_symbol_table(void);
symbol_table add_slc_value_to_table(symbol_table st, const char * name,
    slc_value the_slc_value);
slc_value find_symbol(symbol_table st, const expression the_expr);
void debug_symbol_table(symbol_table st);
void free_symbol_table(symbol_table st);

extern slc_value evaluate_expression(expression the_expression, symbol_table * st);

#endif
