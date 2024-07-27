/**
 * @file   ellipse.c
 * @brief  This file contains the functions related to drawing an ellipse.
 * @author Matthew C. Lindeman
 * @date   July 02, 2023
 * @bug    None known
 * @todo   Nothing
 */
#include "ellipse.h"

ellipse evaluate_ellipse(parsed_shape the_shape, symbol_table * st) {
  double center_x = DEFAULT_ELLIPSE_CENTER_X;
  double center_y = DEFAULT_ELLIPSE_CENTER_Y;

  uint8_t pixel_r = DEFAULT_ELLIPSE_PIXEL_R;
  uint8_t pixel_g = DEFAULT_ELLIPSE_PIXEL_G;
  uint8_t pixel_b = DEFAULT_ELLIPSE_PIXEL_B;

  size_t major_axis = DEFAULT_ELLIPSE_MAJOR_AXIS;
  size_t minor_axis = DEFAULT_ELLIPSE_MINOR_AXIS;

  int thickness = DEFAULT_ELLIPSE_THICKNESS;

  expression tmp_name = {0};
  expression tmp_value = {0};

  for(uint32_t i = 0; i < the_shape.qty_values; i++) {
    tmp_name = the_shape.values[i];
    i++;
    tmp_value = opaque_eval_expr(&the_shape.values[i], st);
    validate_type(tmp_name, VAR, "[EVALUATE_ELLIPSE]: name was not specified before value\n");

    if(!strncmp(tmp_name.value.string_value, "center_x", sizeof("center_x") - 1)) {
      validate_type(tmp_value, DOUBLE, "[EVALUATE_ELLIPSE]: center_x requires a double\n");
      center_x = tmp_value.value.double_value;
    } else if(!strncmp(tmp_name.value.string_value, "center_y", sizeof("center_y") - 1)) {
      validate_type(tmp_value, DOUBLE, "[EVALUATE_ELLIPSE]: center_y requires a double\n");
      center_y = tmp_value.value.double_value;
    } else if(!strncmp(tmp_name.value.string_value, "pixel_r", sizeof("pixel_r") - 1)) {
      validate_type(tmp_value, INT, "[EVALUATE_ELLIPSE]: pixel_r requires an int\n");
      pixel_r = (uint8_t)tmp_value.value.int_value;
    } else if(!strncmp(tmp_name.value.string_value, "pixel_g", sizeof("pixel_g") - 1)) {
      validate_type(tmp_value, INT, "[EVALUATE_ELLIPSE]: pixel_g requires an int\n");
      pixel_g = (uint8_t)tmp_value.value.int_value;
    } else if(!strncmp(tmp_name.value.string_value, "pixel_b", sizeof("pixel_b") - 1)) {
      validate_type(tmp_value, INT, "[EVALUATE_ELLIPSE]: pixel_b requires an int\n");
      pixel_b = (uint8_t)tmp_value.value.int_value;
    } else if(!strncmp(tmp_name.value.string_value, "major_axis", sizeof("major_axis") - 1)) {
      validate_type(tmp_value, INT, "[EVALUATE_ELLIPSE]: major_axis requires a int\n");
      major_axis = (size_t)tmp_value.value.int_value;
    } else if(!strncmp(tmp_name.value.string_value, "minor_axis", sizeof("minor_axis") - 1)) {
      validate_type(tmp_value, INT, "[EVALUATE_ELLIPSE]: minor_axis requires a int\n");
      minor_axis = (size_t)tmp_value.value.int_value;
    } else if(!strncmp(tmp_name.value.string_value, "thickness", sizeof("thickness") - 1)) {
      validate_type(tmp_value, INT, "[EVALUATE_ELLIPSE]: thickness requires a int\n");
      thickness = tmp_value.value.int_value;
    } else {
      fprintf(stderr, "[EVALUATE_ELLIPSE]: unrecognized directive `%s`\n",
          tmp_name.value.string_value);
      exit(1);
    }

    tmp_name = (expression){0};
    tmp_value = (expression){0};
  }
  return (ellipse){
    (coord_2d){center_x, center_y},
    (pixel){pixel_r, pixel_g, pixel_b},
    major_axis,
    minor_axis,
    thickness};
}

/**
 * This function draws an ellipse.
 * @param  the_canvas - The canvas which the ellipse will be drawn to.
 * @param the_ellipse - The ellipse which will be written to the canvas.
 * @return the_canvas - The canvas with the ellipse written to it.
 */
canvas draw_ellipse(canvas the_canvas, ellipse the_ellipse) {
  int center_x = the_ellipse.center.x;
  int center_y = the_ellipse.center.y;
  int radius_x = the_ellipse.major_axis / 2;
  int radius_y = the_ellipse.minor_axis / 2;
  
  int x = 0;
  int y = radius_y;
  int rx2 = radius_x * radius_x;
  int ry2 = radius_y * radius_y;
  int two_rx2 = 2 * rx2;
  int two_ry2 = 2 * ry2;
  int p = 0;

  // Region 1
  int dx = 0;
  int dy = two_rx2 * y;

  the_canvas = draw_ellipse_points(the_canvas, the_ellipse, center_x, center_y,
      x, y);

  // Region 1
  p = ry2 - (rx2 * radius_y) + (0.25 * rx2);

  while(dx < dy) {
    x++;
    dx += two_ry2;
    if (p < 0) {
      p += ry2 + dx;
    } else {
      y--;
      dy -= two_rx2;
      p += ry2 + dx - dy;
    }
    the_canvas = draw_ellipse_points(the_canvas, the_ellipse, center_x,
        center_y, x, y);
  }

  // Region 2
  p = ry2 * (x + 0.5) * (x + 0.5) + rx2 * (y - 1) * (y - 1) - rx2 * ry2;

  while(y > 0) {
    y--;
    dy -= two_rx2;
    if (p > 0) {
      p += rx2 - dy;
    } else {
      x++;
      dx += two_ry2;
      p += rx2 - dy + dx;
    }
    the_canvas = draw_ellipse_points(the_canvas, the_ellipse, center_x,
        center_y, x, y);
  }

  return the_canvas;
}

/**
 * This function is a helper function to draw_ellipse.
 * @param  the_canvas - The canvas which the point will be written to.
 * @param the_ellipse - The ellipse whoe points are being written to the canvas.
 * @param    center_x - The center x point.
 * @param    center_y - The center y point.
 * @param           x - The x value of the point.
 * @param           y - The y value of the point.
 * @return the_canvas - The canvas which will have the points written to it.
 */
canvas draw_ellipse_points(canvas the_canvas, ellipse the_ellipse, int center_x,
    int center_y, int x, int y) {
  for(int i = -the_ellipse.thickness/2; i <= the_ellipse.thickness/2; i++) {
    for(int j = -the_ellipse.thickness/2; j <= the_ellipse.thickness/2; j++) {
      if(center_y + y + i < the_canvas.height && center_y + y + i >= 0
          && center_x + x + j < the_canvas.width && center_x + x + j >= 0) {
        the_canvas.values[center_y + y + i][center_x + x + j] = the_ellipse.color;
      }
      if(center_y + y + i < the_canvas.height && center_y + y + i >= 0
          && center_x - x + j < the_canvas.width && center_x - x + j >= 0) {
        the_canvas.values[center_y + y + i][center_x - x + j] = the_ellipse.color;
      }
      if(center_y - y + i < the_canvas.height && center_y - y + i >= 0
          && center_x + x + j < the_canvas.width && center_x + x + j >= 0) {
        the_canvas.values[center_y - y + i][center_x + x + j] = the_ellipse.color;
      }
      if(center_y - y + i < the_canvas.height && center_y - y + i >= 0
          && center_x - x + j < the_canvas.width && center_x - x + j >= 0) {
        the_canvas.values[center_y - y + i][center_x - x + j] = the_ellipse.color;
      }
    }
  }
  return the_canvas;
}
