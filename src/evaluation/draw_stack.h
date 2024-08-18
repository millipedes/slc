#ifndef DRAW_STACK_H
#define DRAW_STACK_H

#include "evaluation_types.h"

typedef struct DRAW_STACK_T {
  slc_value value[2];
  struct DRAW_STACK_T * prev;
} draw_stack;

draw_stack pop(draw_stack ss);
draw_stack push(draw_stack ss, slc_value value[2]);
void free_draw_stack(draw_stack ss);

#endif
