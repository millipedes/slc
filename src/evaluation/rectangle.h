// /**
//  * @file   rectangle.h
//  * @brief  This file contains the function definitions for rectangle.c.
//  * @date   July 02, 2023
//  * @bug    None known
//  * @todo   N/a
//  */
// #ifndef RECTANGLE_H
// #define RECTANGLE_H
// 
// #include "line.h"
// 
// #define DEFAULT_RECTANGLE_CENTER_X  0
// #define DEFAULT_RECTANGLE_CENTER_Y  0
// 
// #define DEFAULT_RECTANGLE_PIXEL_R   0
// #define DEFAULT_RECTANGLE_PIXEL_G   0
// #define DEFAULT_RECTANGLE_PIXEL_B   0
// #define DEFAULT_RECTANGLE_PIXEL_A   255
// 
// #define DEFAULT_RECTANGLE_HEIGHT    100
// #define DEFAULT_RECTANGLE_WIDTH     100
// 
// #define DEFAULT_RECTANGLE_THICKNESS 10
// 
// typedef struct RECTANGLE_T {
//   coord_2d center;
//   pixel color;
//   size_t height;
//   size_t width;
//   int thickness;
// } rectangle;
// 
// rectangle evaluate_rectangle(parsed_shape the_shape, symbol_table * st);
// canvas draw_rectangle(canvas the_canvas, rectangle the_rect);
// bool point_in_rectangle(rectangle the_rect, coord_2d point);
// 
// #endif
