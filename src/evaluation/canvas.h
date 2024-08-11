/**
 * @file   canvas.h
 * @brief  This file contains the function definitions for canvas.c.
 * @author Matthew C. Lindeman
 * @date   January 30, 2024
 * @bug    None known
 * @todo   Nothing
 */
#ifndef CAN_H
#define CAN_H

#include <png.h>

#include "../parsing/parsing_ds.h"

#define MAX_COL 255
#define MIN_COL 0

#define DEFAULT_CANVAS_PIXEL_R 0
#define DEFAULT_CANVAS_PIXEL_G 0
#define DEFAULT_CANVAS_PIXEL_B 0
#define DEFAULT_CANVAS_PIXEL_A 255
#define DEFAULT_CANVAS_HEIGHT  1000
#define DEFAULT_CANVAS_WIDTH   1000

typedef struct PIXEL_T {
  uint8_t r;
  uint8_t g;
  uint8_t b;
  uint8_t a;
} pixel;

typedef struct CANVAS_T {
  pixel ** values;
  int height;
  int width;
} canvas;

struct SYMBOL_TABLE_T;
typedef struct SYMBOL_TABLE_T symbol_table;
canvas evaluate_canvas(parsed_shape the_shape, symbol_table * st);

canvas init_canvas(int height, int width, uint8_t r, uint8_t g, uint8_t b, uint8_t a);
void write_canvas_png(canvas the_canvas, const char * file_name);
canvas read_canvas_png(const char *file_name);
void free_canvas(canvas the_canvas);

extern expression opaque_eval_expr(expression * value, symbol_table * st);

#endif
