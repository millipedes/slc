#include "evaluation_drawing.h"

void draw_shape(parsed_lline the_lline, symbol_table * st) {
  shape the_shape = {0};
  if(the_lline.qty_values == 1) {
    switch(the_lline.value_type[0]) {
      case EXPR:
        the_shape = evaluate_expression(the_lline.value[0].the_expr, st).value.the_shape;
        draw_shape_blank_canvas(the_shape, get_default_file_name());
        break;
      case SHAPE:
        the_shape = evaluate_shape(the_lline.value[0].the_shape, st).value.the_shape;
        draw_shape_blank_canvas(the_shape, get_default_file_name());
        break;
      case ARRAY:
        fprintf(stderr, "[DRAW_SHAPE]: Arrays cannot be drawn\n");
        exit(1);
    }
    free_shape(the_shape);
  } else if(the_lline.qty_values == 2) {
    if(the_lline.value_type[0] == ARRAY || the_lline.value_type[1] == ARRAY) {
      fprintf(stderr, "[DRAW_SHAPE]: Arrays cannot be drawn\n");
      exit(1);
    }
    slc_value maybe_canvas = {0};
    if(the_lline.value_type[0] == SHAPE) {
      if(the_lline.value[1].the_expr.type == VAR) {
        maybe_canvas = find_symbol(*st, the_lline.value[1].the_expr);
        maybe_canvas.value.the_shape.value.the_canvas = write_shape_to_canvas(
              evaluate_shape(the_lline.value[0].the_shape, st).value.the_shape,
              maybe_canvas);
      } else if(the_lline.value[1].the_expr.type == STRING) {
        the_shape = evaluate_shape(the_lline.value[0].the_shape, st).value.the_shape;
        write_shape_to_file(the_shape, the_lline.value[1].the_expr.value.string_value);
        free_shape(the_shape);
      }
    } else if(the_lline.value_type[0] == EXPR) {
      if(the_lline.value[0].the_expr.type == VAR
          && the_lline.value[1].the_expr.type == VAR) {
        maybe_canvas = find_symbol(*st, the_lline.value[1].the_expr);
        maybe_canvas.value.the_shape.value.the_canvas = write_shape_to_canvas(
              evaluate_shape(the_lline.value[0].the_shape, st).value.the_shape,
              maybe_canvas);
      } else if(the_lline.value[0].the_expr.type == VAR
          && the_lline.value[1].the_expr.type == STRING) {
        the_shape = find_symbol(*st, the_lline.value[0].the_expr).value.the_shape;
        write_shape_to_file(the_shape, the_lline.value[1].the_expr.value.string_value);
      }
    } else {
      fprintf(stderr, "[DRAW_SHAPE]: unknown error\n");
      exit(1);
    }
  } else {
    fprintf(stderr, "[DRAW_SHAPE]: Logical line with more than 2 (or 0) "
        " values passed\n");
    exit(1);
  }
}

bool file_exists(const char * file_name) {
  return access(file_name, F_OK) == 0 ? true : false;
}

canvas write_shape_to_canvas(shape the_shape, slc_value the_slc_value) {
  canvas the_canvas = the_slc_value.value.the_shape.value.the_canvas;
  rectangle the_rectangle = the_shape.value.the_rectangle;
  ellipse the_ellipse = the_shape.value.the_ellipse;
  line the_line = the_shape.value.the_line;
  switch(the_shape.type) {
    case RECTANGLE:
      the_canvas = draw_rectangle(the_canvas, the_rectangle);
      break;
    case ELLIPSE:
      the_canvas = draw_ellipse(the_canvas, the_ellipse);
      break;
    case LINE:
      the_canvas = draw_line(the_canvas, the_line);
      break;
    case CANVAS:
      fprintf(stderr, "[WRITE_SHAPE_TO_CANVAS]: writing a canvas to a canvas is "
          "not supported\n");
      exit(1);
  }
  return the_canvas;
}

void write_shape_to_file(shape the_shape, const char * file_name) {
  rectangle the_rectangle = the_shape.value.the_rectangle;
  ellipse the_ellipse = the_shape.value.the_ellipse;
  line the_line = the_shape.value.the_line;
  canvas the_canvas = {0};
  if(file_exists(file_name)) {
    switch(the_shape.type) {
      case RECTANGLE:
        the_canvas = read_canvas_png(file_name);
        the_canvas = draw_rectangle(the_canvas, the_rectangle);
        break;
      case ELLIPSE:
        the_canvas = read_canvas_png(file_name);
        the_canvas = draw_ellipse(the_canvas, the_ellipse);
        break;
      case LINE:
        the_canvas = read_canvas_png(file_name);
        the_canvas = draw_line(the_canvas, the_line);
        break;
      case CANVAS:
        write_canvas_png(the_shape.value.the_canvas, file_name);
        free_canvas(the_canvas);
        return;
    }
    free_canvas(the_canvas);
  } else {
    if(the_shape.type == CANVAS) {
      write_canvas_png(the_shape.value.the_canvas, file_name);
    } else {
      draw_shape_blank_canvas(the_shape, file_name);
    }
  }
}

void draw_shape_blank_canvas(shape the_shape, const char * file_name) {
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
    case CANVAS:
      write_canvas_png(the_shape.value.the_canvas, file_name);
      return;
  }
  write_canvas_png(the_canvas, file_name);
  free_canvas(the_canvas);
}
