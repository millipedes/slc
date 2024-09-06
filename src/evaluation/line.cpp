// /**
//  * @file   line.c
//  * @brief  This file contains the functions related to drawing lines onto a
//  * canvas.
//  * @author Matthew C. Lindeman
//  * @date   July 23, 2023
//  * @bug    None known
//  * @todo   Write the dotten line style implementation.
//  */
// #include "line.h"
// 
// line evaluate_line(parsed_shape the_shape, symbol_table * st) {
//   double to_x = DEFAULT_LINE_TO_X;
//   double to_y = DEFAULT_LINE_TO_Y;
// 
//   double from_x = DEFAULT_LINE_FROM_X;
//   double from_y = DEFAULT_LINE_FROM_Y;
// 
//   uint8_t pixel_r = DEFAULT_LINE_PIXEL_R;
//   uint8_t pixel_g = DEFAULT_LINE_PIXEL_G;
//   uint8_t pixel_b = DEFAULT_LINE_PIXEL_B;
//   uint8_t pixel_a = DEFAULT_LINE_PIXEL_A;
// 
//   int thickness = DEFAULT_LINE_THICKNESS;
// 
//   expression tmp_name = {0};
//   expression tmp_value = {0};
// 
//   for(uint32_t i = 0; i < the_shape.qty_values; i++) {
//     tmp_name = the_shape.values[i];
//     i++;
//     tmp_value = opaque_eval_expr(&the_shape.values[i], st);
//     validate_type(tmp_name, VAR, "[EVALUATE_LINE]: name was not specified before value\n");
// 
//     if(!strncmp(tmp_name.value.string_value, "to_x", sizeof("to_x") - 1)) {
//       validate_type(tmp_value, DOUBLE, "[EVALUATE_LINE]: to_x requires a double\n");
//       to_x = tmp_value.value.double_value;
//     } else if(!strncmp(tmp_name.value.string_value, "to_y", sizeof("to_y") - 1)) {
//       validate_type(tmp_value, DOUBLE, "[EVALUATE_LINE]: to_y requires a double\n");
//       to_y = tmp_value.value.double_value;
//     } else if(!strncmp(tmp_name.value.string_value, "from_x", sizeof("from_x") - 1)) {
//       validate_type(tmp_value, DOUBLE, "[EVALUATE_LINE]: from_x requires a double\n");
//       from_x = tmp_value.value.double_value;
//     } else if(!strncmp(tmp_name.value.string_value, "from_y", sizeof("from_y") - 1)) {
//       validate_type(tmp_value, DOUBLE, "[EVALUATE_LINE]: from_y requires a double\n");
//       from_y = tmp_value.value.double_value;
//     } else if(!strncmp(tmp_name.value.string_value, "pixel_r", sizeof("pixel_r") - 1)) {
//       validate_type(tmp_value, INT, "[EVALUATE_LINE]: pixel_r requires an int\n");
//       pixel_r = (uint8_t)tmp_value.value.int_value;
//     } else if(!strncmp(tmp_name.value.string_value, "pixel_g", sizeof("pixel_g") - 1)) {
//       validate_type(tmp_value, INT, "[EVALUATE_LINE]: pixel_g requires an int\n");
//       pixel_g = (uint8_t)tmp_value.value.int_value;
//     } else if(!strncmp(tmp_name.value.string_value, "pixel_b", sizeof("pixel_b") - 1)) {
//       validate_type(tmp_value, INT, "[EVALUATE_LINE]: pixel_b requires an int\n");
//       pixel_b = (uint8_t)tmp_value.value.int_value;
//     } else if(!strncmp(tmp_name.value.string_value, "pixel_a", sizeof("pixel_a") - 1)) {
//       validate_type(tmp_value, INT, "[EVALUATE_LINE]: pixel_a requires an int\n");
//       pixel_a = (uint8_t)tmp_value.value.int_value;
//     } else if(!strncmp(tmp_name.value.string_value, "thickness", sizeof("thickness") - 1)) {
//       validate_type(tmp_value, INT, "[EVALUATE_LINE]: thickness requires a int\n");
//       thickness = tmp_value.value.int_value;
//     } else {
//       fprintf(stderr, "[EVALUATE_LINE]: unrecognized directive `%s`\n",
//           tmp_name.value.string_value);
//       exit(1);
//     }
// 
//     tmp_name = (expression){0};
//     tmp_value = (expression){0};
//   }
//   return (line){
//     (coord_2d){to_x, to_y},
//     (coord_2d){from_x, from_y},
//     (pixel){pixel_r, pixel_g, pixel_b, pixel_a},
//     thickness};
// }
// 
// /**
//  * This function uses bresenham's line drawing algorithm to write a solid style
//  * line to a canvas.
//  * @param  the_canvas - The canvas for the line to be written to.
//  * @param    the_line - The line to be written to the canvas.
//  * @return the_canvas - The canvas with the line written to it.
//  */
// canvas draw_line(canvas the_canvas, line the_line) {
//   int dx = the_line.to.x - the_line.from.x;
//   int dy = the_line.to.y - the_line.from.y;
//   int x = the_line.from.x;
//   int y = the_line.from.y;
// 
//   int x_inc = (dx > 0) ? 1 : -1;
//   int y_inc = (dy > 0) ? 1 : -1;
// 
//   dx = abs(dx);
//   dy = abs(dy);
// 
//   int two_dx = 2 * dx;
//   int two_dy = 2 * dy;
// 
//   int error = 0;
// 
//   if(dx >= dy) {
//     while(x != the_line.to.x) {
//       for(int i = 0; i < the_line.thickness; i++) {
//         for(int j = -the_line.thickness / 2; j <= the_line.thickness / 2;
//             j++) {
//           if(y + j < the_canvas.height && y + j >= 0
//               && (int)x + i < the_canvas.width && (int)x + i >=0)
//             the_canvas.values[y + j][(int)x + i] = the_line.color;
//         }
//       }
//       x += x_inc;
//       error += two_dy;
//       if (error > dx) {
//         y += y_inc;
//         error -= two_dx;
//       }
//     }
//   } else {
//     while(y != the_line.to.y) {
//       for(int i = 0; i < the_line.thickness; i++) {
//         for(int j = -the_line.thickness / 2; j <= the_line.thickness / 2;
//             j++) {
//           if(y + j < the_canvas.height && y + j >= 0
//               && (int)x + i < the_canvas.width && (int)x + i >=0)
//             the_canvas.values[y + j][(int)x + i] = the_line.color;
//         }
//       }
//       y += y_inc;
//       error += two_dx;
//       if(error > dy) {
//         x += x_inc;
//         error -= two_dy;
//       }
//     }
//   }
// 
//   return the_canvas;
// }
// 
// canvas draw_b_curve(canvas the_canvas, line the_line, points the_points) {
//   for(double i = 0.0; i < 1.0; i += B_CURVE_DELTA) {
//     coord_2d at_t = de_casteljau(the_points, i);
//     for(int j = -(int)((double)the_line.thickness/2.0);
//         j < (int)((double)the_line.thickness/2.0); j++) {
//       for(int k = 0; k < the_line.thickness; k++) {
//         if(at_t.y + j < the_canvas.height && at_t.y + j >= 0
//             && at_t.x + k < the_canvas.width && at_t.x + k >= 0) {
//           the_canvas.values[(int)at_t.y + j][((int)at_t.x + k)] = the_line.color;
//         }
//       }
//     }
//   }
//   return the_canvas;
// }
// 
// coord_2d de_casteljau(points the_points, double t) {
//   points tmp = deep_copy_points(the_points);
//   coord_2d result = {0};
//   for(uint32_t i = 1; i <= the_points.qty_points; i++) {
//     for(uint32_t j = 0; j < the_points.qty_points - i; j++) {
//       tmp.value[j].x = tmp.value[j].x * (1 - t) + tmp.value[j + 1].x * t;
//       tmp.value[j].y = tmp.value[j].y * (1 - t) + tmp.value[j + 1].y * t;
//     }
//   }
//   result.x = tmp.value[0].x;
//   result.y = tmp.value[0].y;
//   free_points(tmp);
//   return result;
// }
