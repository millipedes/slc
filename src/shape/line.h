/**
 * @file   line.h.
 * @brief  This file contains the function definitions for line.c.
 * @author Matthew C. Lindeman
 * @date   July 23, 2023
 * @bug    None known
 * @todo   Write the dotten line style implementation.
 */
#ifndef LINE_H
#define LINE_H

#include "../canvas/canvas.h"
#include "coordinate.h"
#include "../parsing/parsing.h"

#define DEFAULT_LINE_THICKNESS 10
#define DEFAULT_LINE_TO_X 0
#define DEFAULT_LINE_TO_Y 0
#define DEFAULT_LINE_FROM_X 1
#define DEFAULT_LINE_FROM_Y 1

typedef struct LINE_T {
  coord_2d to;
  coord_2d from;
  pixel color;
  int thickness;
} line;

canvas bresenham_line_draw(canvas the_canvas, line the_line);

#endif
