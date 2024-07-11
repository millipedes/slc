/**
 * @file   line.c
 * @brief  This file contains the functions related to drawing lines onto a
 * canvas.
 * @author Matthew C. Lindeman
 * @date   July 23, 2023
 * @bug    None known
 * @todo   Write the dotten line style implementation.
 */
#include "line.h"

/**
 * This function uses bresenham's line drawing algorithm to write a solid style
 * line to a canvas.
 * @param  the_canvas - The canvas for the line to be written to.
 * @param    the_line - The line to be written to the canvas.
 * @return the_canvas - The canvas with the line written to it.
 */
canvas bresenham_line_draw(canvas the_canvas, line the_line) {
  int dx = the_line.to.x - the_line.from.x;
  int dy = the_line.to.y - the_line.from.y;
  int x = the_line.from.x;
  int y = the_line.from.y;

  int x_inc = (dx > 0) ? 1 : -1;
  int y_inc = (dy > 0) ? 1 : -1;

  dx = abs(dx);
  dy = abs(dy);

  int two_dx = 2 * dx;
  int two_dy = 2 * dy;

  int error = 0;

  if(dx >= dy) {
    while(x != the_line.to.x) {
      for(int i = 0; i < the_line.thickness; i++) {
        for(int j = -the_line.thickness / 2; j <= the_line.thickness / 2;
            j++) {
          if(y + j < the_canvas.height && y + j >= 0
              && (int)x + i < the_canvas.width && (int)x + i >=0)
            the_canvas.values[y + j][(int)x + i] = the_line.color;
        }
      }
      x += x_inc;
      error += two_dy;
      if (error > dx) {
        y += y_inc;
        error -= two_dx;
      }
    }
  } else {
    while(y != the_line.to.y) {
      for(int i = 0; i < the_line.thickness; i++) {
        for(int j = -the_line.thickness / 2; j <= the_line.thickness / 2;
            j++) {
          if(y + j < the_canvas.height && y + j >= 0
              && (int)x + i < the_canvas.width && (int)x + i >=0)
            the_canvas.values[y + j][(int)x + i] = the_line.color;
        }
      }
      y += y_inc;
      error += two_dx;
      if(error > dy) {
        x += x_inc;
        error -= two_dy;
      }
    }
  }

  return the_canvas;
}
