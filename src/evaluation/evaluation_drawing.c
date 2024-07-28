#include "evaluation_drawing.h"

void draw_shape(parsed_lline the_lline, symbol_table st) {
  if(the_lline.qty_values == 1) {
    draw_shape_blank_canvas(evaluate_shape(the_lline.value[0].the_shape, &st).value.the_shape);
  } else if(the_lline.qty_values == 2) {
    // add -> interface here
  } else {
    fprintf(stderr, "[DRAW_SHAPE]: Logical line with more than 2 (or 0) "
        " values passed\n");
    exit(1);
  }
}

void draw_shape_blank_canvas(shape the_shape) {
  int height = 0;
  int width = 0;
  rectangle the_rectangle = the_shape.value.the_rectangle;
  ellipse the_ellipse = the_shape.value.the_ellipse;
  line the_line = the_shape.value.the_line;
  canvas the_canvas = {0};
  switch(the_shape.type) {
    case RECTANGLE:
      height = the_rectangle.height + the_rectangle.center.y + the_rectangle.thickness;
      width = the_rectangle.width + the_rectangle.center.x + the_rectangle.thickness;
      the_canvas = init_canvas(height, width, MAX_COL, MAX_COL, MAX_COL, MIN_COL);
      the_canvas = draw_rectangle(the_canvas, the_rectangle);
      break;
    case ELLIPSE:
      height = the_ellipse.major_axis + the_ellipse.center.y + the_ellipse.thickness;
      width = the_ellipse.minor_axis + the_ellipse.center.x + the_ellipse.thickness;
      the_canvas = init_canvas(height, width, MAX_COL, MAX_COL, MAX_COL, MIN_COL);
      the_canvas = draw_ellipse(the_canvas, the_ellipse);
      break;
    case LINE:
      height = (the_line.to.x > the_line.from.x) ?
        the_line.to.x + the_line.thickness : the_line.from.x + the_line.thickness;
      width = (the_line.to.y > the_line.from.y) ?
        the_line.to.y + the_line.thickness : the_line.from.y + the_line.thickness;
      the_canvas = init_canvas(height, width, MAX_COL, MAX_COL, MAX_COL, MIN_COL);
      the_canvas = draw_line(the_canvas, the_line);
      break;
  }
  write_canvas_png(the_canvas, get_default_file_name());
  free_canvas(the_canvas);
}
