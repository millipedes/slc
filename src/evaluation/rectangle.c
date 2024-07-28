/**
 * @file   rectangle.c
 * @brief  This file contains the functions for writing a rectangle.
 * @author Matthew C. Lindeman
 * @date   July 02, 2023
 * @bug    None known
 * @todo   N/a
 */
#include "rectangle.h"

rectangle evaluate_rectangle(parsed_shape the_shape, symbol_table * st) {
  double center_x = DEFAULT_RECTANGLE_CENTER_X;
  double center_y = DEFAULT_RECTANGLE_CENTER_Y;

  uint8_t pixel_r = DEFAULT_RECTANGLE_PIXEL_R;
  uint8_t pixel_g = DEFAULT_RECTANGLE_PIXEL_G;
  uint8_t pixel_b = DEFAULT_RECTANGLE_PIXEL_B;
  uint8_t pixel_a = DEFAULT_RECTANGLE_PIXEL_A;

  size_t height = DEFAULT_RECTANGLE_HEIGHT;
  size_t width = DEFAULT_RECTANGLE_WIDTH;

  int thickness = DEFAULT_RECTANGLE_THICKNESS;

  expression tmp_name = {0};
  expression tmp_value = {0};

  for(uint32_t i = 0; i < the_shape.qty_values; i++) {
    tmp_name = the_shape.values[i];
    i++;
    tmp_value = opaque_eval_expr(&the_shape.values[i], st);
    validate_type(tmp_name, VAR, "[EVALUATE_RECTANGLE]: name was not specified before value\n");

    if(!strncmp(tmp_name.value.string_value, "center_x", sizeof("center_x") - 1)) {
      validate_type(tmp_value, DOUBLE, "[EVALUATE_RECTANGLE]: center_x requires a double\n");
      center_x = tmp_value.value.double_value;
    } else if(!strncmp(tmp_name.value.string_value, "center_y", sizeof("center_y") - 1)) {
      validate_type(tmp_value, DOUBLE, "[EVALUATE_RECTANGLE]: center_y requires a double\n");
      center_y = tmp_value.value.double_value;
    } else if(!strncmp(tmp_name.value.string_value, "pixel_r", sizeof("pixel_r") - 1)) {
      validate_type(tmp_value, INT, "[EVALUATE_RECTANGLE]: pixel_r requires an int\n");
      pixel_r = (uint8_t)tmp_value.value.int_value;
    } else if(!strncmp(tmp_name.value.string_value, "pixel_g", sizeof("pixel_g") - 1)) {
      validate_type(tmp_value, INT, "[EVALUATE_RECTANGLE]: pixel_g requires an int\n");
      pixel_g = (uint8_t)tmp_value.value.int_value;
    } else if(!strncmp(tmp_name.value.string_value, "pixel_b", sizeof("pixel_b") - 1)) {
      validate_type(tmp_value, INT, "[EVALUATE_RECTANGLE]: pixel_b requires an int\n");
      pixel_b = (uint8_t)tmp_value.value.int_value;
    } else if(!strncmp(tmp_name.value.string_value, "pixel_a", sizeof("pixel_a") - 1)) {
      validate_type(tmp_value, INT, "[EVALUATE_RECTANGLE]: pixel_a requires an int\n");
      pixel_a = (uint8_t)tmp_value.value.int_value;
    } else if(!strncmp(tmp_name.value.string_value, "height", sizeof("height") - 1)) {
      validate_type(tmp_value, INT, "[EVALUATE_RECTANGLE]: height requires a int\n");
      height = (size_t)tmp_value.value.int_value;
    } else if(!strncmp(tmp_name.value.string_value, "width", sizeof("width") - 1)) {
      validate_type(tmp_value, INT, "[EVALUATE_RECTANGLE]: width requires a int\n");
      width = (size_t)tmp_value.value.int_value;
    } else if(!strncmp(tmp_name.value.string_value, "thickness", sizeof("thickness") - 1)) {
      validate_type(tmp_value, INT, "[EVALUATE_RECTANGLE]: thickness requires a int\n");
      thickness = tmp_value.value.int_value;
    } else {
      fprintf(stderr, "[EVALUATE_RECTANGLE]: unrecognized directive `%s`\n",
          tmp_name.value.string_value);
      exit(1);
    }

    tmp_name = (expression){0};
    tmp_value = (expression){0};
  }
  return (rectangle){
    (coord_2d){center_x, center_y},
    (pixel){pixel_r, pixel_g, pixel_b, pixel_a},
    height,
    width,
    thickness};
}

/**
 * This function writes a rectangle to a canvas.
 * @param  the_canvas - The canvas for the rectangle to be drawn onto.
 * @param    the_rect - The rectangle which will be drawn onto the cavas.
 * @return the_canvas - The canvas with the rectangle drawn onto it.
 */
canvas draw_rectangle(canvas the_canvas, rectangle the_rect) {
  int half_width = the_rect.width / 2;
  int half_height = the_rect.height / 2;
  double x1 = (double)(the_rect.center.x - half_width);
  double y1 = (double)(the_rect.center.y - half_height);
  double x2 = (double)(the_rect.center.x + half_width);
  double y2 = (double)(the_rect.center.y + half_height);

  // Draw the four sides of the rectangle
  draw_line(the_canvas, (line){
      (coord_2d){x1, y1}, (coord_2d){x2, y1}, the_rect.color, the_rect.thickness});
  draw_line(the_canvas, (line){
      (coord_2d){x2, y1}, (coord_2d){x2, y2}, the_rect.color, the_rect.thickness});
  draw_line(the_canvas, (line){
      (coord_2d){x2, y2}, (coord_2d){x1, y2}, the_rect.color, the_rect.thickness});
  draw_line(the_canvas, (line){
      (coord_2d){x1, y2}, (coord_2d){x1, y1}, the_rect.color, the_rect.thickness});

  return the_canvas;
}
