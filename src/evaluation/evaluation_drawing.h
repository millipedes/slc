#ifndef EVALUATION_DRAWING_H
#define EVALUATION_DRAWING_H

#include <unistd.h>

#include "evaluation_types.h"
#include "../io/default_output_file.h"
#include "../parsing/parsing_ds.h"
#include "symbol_table.h"

void draw_shape(parsed_lline the_lline, symbol_table * st);
canvas write_shape_to_canvas(shape the_shape, slc_value the_slc_value);
void write_shape_to_file(shape the_shape, const char * file_name);
void draw_shape_blank_canvas(shape the_shape, const char * file_name);

extern slc_value evaluate_shape(parsed_shape the_shape, symbol_table * st);

#endif
