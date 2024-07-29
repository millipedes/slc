#include "symbol_table.h"

size_t djb2_hash(const char * value) {
  size_t value_len = strnlen(value, MAX_STR);
  size_t hash_value = DJB2_HASH_VALUE;
  for(size_t i = 0; i < value_len; i++)
    hash_value = (hash_value * DJB2_HASH_MULTIPLE) ^ (size_t)value[i];
  return hash_value % QTY_BUCKETS;
}

slc_value_ll init_slc_value_ll(const char * name, slc_value the_slc_value) {
  slc_value_ll the_slc_value_ll = {0};
  size_t name_len = strnlen(name, MAX_STR) + 1;
  the_slc_value_ll.name = (char *)calloc(name_len, sizeof(char));
  strncpy(the_slc_value_ll.name, name, name_len);
  the_slc_value_ll.value = the_slc_value;
  the_slc_value_ll.next = NULL;
  return the_slc_value_ll;
}

slc_value slc_value_in_list(slc_value_ll the_slc_value_ll, const expression the_expr, const symbol_table st) {
  if(!strncmp(the_slc_value_ll.name, the_expr.value.string_value, MAX_STR)) {
    if(the_expr.qty_children == 0) {
      return the_slc_value_ll.value;
    } else if(the_expr.child[0].type == ARRAY_ACCESSOR) {
      expression accessor_parent = the_expr;
      return get_value_from_array(the_slc_value_ll.value, accessor_parent, st, 0);
    } else {
      fprintf(stderr, "[SLC_VALUE_IN_LIST]: VAR had a non-accessor child\n");
      exit(1);
    }
  } else if(the_slc_value_ll.next)
    return slc_value_in_list(*the_slc_value_ll.next, the_expr, st);
  else
    return (slc_value){0};
}

slc_value get_value_from_array(slc_value value, const expression the_expr, symbol_table st, int i_deep) {
  expression index = evaluate_expression(the_expr.child[0].child[i_deep], &st).value.the_expr;
  if(index.type != INT) {
    fprintf(stderr, "[GET_VALUE_FROM_ARRAY]: only integer indecies are supported\n");
    exit(1);
  }
  if(index.value.int_value > value.value.the_array[0].qty_values) {
    fprintf(stderr, "[GET_VALUE_FROM_ARRAY]: index %d out of range of array with name `%s`, of size %lu\n",
        index.value.int_value, the_expr.value.string_value, value.value.the_array[0].qty_values);
    exit(1);
  }
  if(i_deep == the_expr.child[0].qty_children - 1) {
    return (slc_value){value.value.the_array[0].value[index.value.int_value],
        value.value.the_array[0].value_type[index.value.int_value]};
  } else {
    return get_value_from_array((slc_value){value.value.the_array[0].value[index.value.int_value],
        value.value.the_array[0].value_type[index.value.int_value]}, the_expr, st, i_deep + 1);
  }
}

slc_value_ll update_slc_value_ll(slc_value_ll head, slc_value_ll tail) {
  if(!head.name)
    return tail;
  slc_value_ll * tmp = &head;
  while(tmp->next) {
    if(!strncmp(tmp->name, tail.name, MAX_STR)) {
      free(tail.name);
      free_slc_value(tmp->value);
      tmp->value = tail.value;
      return head;
    }
    tmp = tmp->next;
  }
  if(!strncmp(tmp->name, tail.name, MAX_STR)) {
    free(tail.name);
    free_slc_value(tmp->value);
    tmp->value = tail.value;
    return head;
  }
  tmp->next = (struct SLC_VALUE_LL_T *)calloc(1, sizeof(struct SLC_VALUE_LL_T));
  *tmp->next = tail;
  return head;
}

void free_slc_value_ll(slc_value_ll the_slc_value_ll) {
  if(the_slc_value_ll.name) {
    free(the_slc_value_ll.name);
  }

  free_slc_value(the_slc_value_ll.value);
  if(the_slc_value_ll.next) {
    free_slc_value_ll(*the_slc_value_ll.next);
  }

  if(the_slc_value_ll.next) {
    free(the_slc_value_ll.next);
  }
}

symbol_table add_slc_value_to_table(symbol_table st, const char * name,
    slc_value the_slc_value) {
  size_t key = djb2_hash(name);
  st.values[key] = update_slc_value_ll(st.values[key],
      init_slc_value_ll(name, the_slc_value));
  return st;
}

slc_value find_symbol(symbol_table st, const expression the_expr) {
  size_t hash_value = djb2_hash(the_expr.value.string_value);
  return slc_value_in_list(st.values[hash_value], the_expr, st);
}

void free_symbol_table(symbol_table st) {
  for(int i = 0; i < QTY_BUCKETS; i++)
    free_slc_value_ll(st.values[i]);
}
