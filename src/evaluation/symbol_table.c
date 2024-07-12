#include "symbol_table.h"

size_t djb2_hash(const char * value) {
  size_t value_len = strnlen(value, MAX_STR);
  size_t hash_value = DJB2_HASH_VALUE;
  for(size_t i = 0; i < value_len; i++)
    hash_value = (hash_value * DJB2_HASH_MULTIPLE) ^ (size_t)value[i];
  return hash_value % QTY_BUCKETS;
}

symbol_table add_slc_value_to_table(symbol_table st, const char * name,
    slc_value the_slc_value) {
  size_t key = djb2_hash(name);
  st.values[key] = update_slc_value_ll(st.values[key],
      init_slc_value_ll(name, the_slc_value));
  return st;
}

slc_value find_symbol(symbol_table st, const char * name) {
  size_t hash_value = djb2_hash(name);
  return slc_value_in_list(st.values[hash_value], name);
}

void free_symbol_table(symbol_table st) {
  for(int i = 0; i < QTY_BUCKETS; i++)
    free_slc_value_ll(st.values[i]);
}
