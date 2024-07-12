#include "linked_list.h"

slc_value_ll init_slc_value_ll(const char * name, slc_value the_slc_value) {
  slc_value_ll the_slc_value_ll = {0};
  size_t name_len = strnlen(name, MAX_STR) + 1;
  the_slc_value_ll.name = (char *)calloc(name_len, sizeof(char));
  strncpy(the_slc_value_ll.name, name, name_len);
  the_slc_value_ll.value = the_slc_value;
  the_slc_value_ll.next = NULL;
  return the_slc_value_ll;
}

slc_value slc_value_in_list(slc_value_ll the_slc_value_ll, const char * name) {
  if(!strncmp(the_slc_value_ll.name, name, MAX_STR))
    return the_slc_value_ll.value;
  else if(the_slc_value_ll.next)
    return slc_value_in_list(*the_slc_value_ll.next, name);
  else
    return (slc_value){0};
}

slc_value_ll update_slc_value_ll(slc_value_ll head, slc_value_ll tail) {
  if(!head.name)
    return tail;
  slc_value_ll * tmp = &head;
  while(tmp->next) {
    if(!strncmp(tmp->name, tail.name, MAX_STR)) {
      free(tail.name);
      tmp->value = tail.value;
      return head;
    }
    tmp = tmp->next;
  }
  if(!strncmp(tmp->name, tail.name, MAX_STR)) {
    free(tail.name);
    tmp->value = tail.value;
    return head;
  }
  tmp->next = (struct SLC_VALUE_LL_T *)calloc(1, sizeof(struct SLC_VALUE_LL_T));
  *tmp->next = tail;
  return head;
}

void free_slc_value_ll(slc_value_ll the_slc_value_ll) {
  if(the_slc_value_ll.name)
    free(the_slc_value_ll.name);
  if(the_slc_value_ll.next)
    free_slc_value_ll(*the_slc_value_ll.next);
  if(the_slc_value_ll.next)
    free(the_slc_value_ll.next);
}
