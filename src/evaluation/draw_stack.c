#include "draw_stack.h"

draw_stack pop(draw_stack ds) {
  if(ds.prev) {
    draw_stack tmp = *ds.prev;
    free_slc_value(ds.value[0]);
    free_slc_value(ds.value[1]);
    free(ds.prev);
    return tmp;
  } else {
    free_slc_value(ds.value[0]);
    free_slc_value(ds.value[1]);
    ds.value[0] = (slc_value){0};
    ds.value[1] = (slc_value){0};
    ds.prev = NULL;
    return ds;
  }
}

draw_stack push(draw_stack ds, slc_value value[2]) {
  draw_stack tmp = ds;
  tmp.prev = (draw_stack *)calloc(1, sizeof(struct DRAW_STACK_T));
  *tmp.prev = ds;
  tmp.value[0] = value[0];
  tmp.value[1] = value[1];
  return tmp;
}

void free_draw_stack(draw_stack ds) {
  while(ds.prev) {
    ds = pop(ds);
  }
}
