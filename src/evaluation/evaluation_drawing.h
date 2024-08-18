#ifndef EVALUATION_DRAWING_H
#define EVALUATION_DRAWING_H

#include <unistd.h>

#include "evaluation_types.h"
#include "../io/default_output_file.h"
#include "../parsing/parsing_ds.h"
#include "symbol_table.h"

typedef enum {
  VAR_VAR,      // draw(the_rect)   -> the_canvas;
  SHAPE_SHAPE,  // draw(ellipse())  -> canvas();
  VAR_STRING,   // draw(the_canvas) -> "out.png";
  VAR_SHAPE,    // draw(the_rect)   -> canvas();
  SHAPE_VAR,    // draw(ellipse())  -> the_canvas;
  SHAPE_STRING, // draw(ellipse())  -> "out.png";
} draw_pairs;

void draw_shape(parsed_lline the_lline, symbol_table * st);
void map_operator(parsed_lline the_lline, symbol_table * st);
draw_pairs determine_draw_pairs(parsed_lline the_lline);
canvas write_shape_to_canvas(shape the_shape, slc_value the_slc_value);
void write_shape_to_file(shape the_shape, const char * file_name);
void draw_shape_blank_canvas(shape the_shape, const char * file_name);

extern slc_value evaluate_shape(parsed_shape the_shape, symbol_table * st);

#endif
