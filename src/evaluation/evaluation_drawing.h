#ifndef EVALUATION_DRAWING_H
#define EVALUATION_DRAWING_H

#include "evaluation_types.h"
#include "../io/default_output_file.h"
#include "../parsing/parsing_ds.h"
#include "symbol_table.h"

void draw_shape(parsed_lline the_lline, symbol_table st);
void draw_shape_blank_canvas(shape the_shape);

extern slc_value evaluate_shape(parsed_shape the_shape, symbol_table * st);

#endif
