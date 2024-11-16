#include "line.h"

namespace SLCEvaluation {

auto Line::operator==(const Line& other) const -> bool {
  return to == other.to
    && from == other.from
    && color == other.color
    && thickness == other.thickness;
}

auto Line::debug() -> void {
  std::cout << "To: " << std::endl;
  to.debug();
  std::cout << "From: " << std::endl;
  from.debug();
  std::cout << "Color: " << std::endl;
  color.debug();
  std::cout << "Thickness: " << thickness << std::endl;
}

auto evaluate_line(slcp::Expr& expr, SymbolTableStack& sts) -> Line {
  double to_x = default_line_to_x;
  double to_y = default_line_to_y;

  double from_x = default_line_from_x;
  double from_y = default_line_from_y;

  uint8_t pixel_r = default_line_pixel_r;
  uint8_t pixel_g = default_line_pixel_g;
  uint8_t pixel_b = default_line_pixel_b;
  uint8_t pixel_a = default_line_pixel_a;

  int thickness = default_line_thickness;

  auto local_canvas_sts = std::stack<SymbolTable>();
  local_canvas_sts.push(SymbolTable());
  read_in_values(expr.child()[0], local_canvas_sts);

  if (extract_value<int, double>(local_canvas_sts, "pixel_r")) {
    pixel_r = *extract_value<int, double>(local_canvas_sts, "pixel_r");
  }
  if (extract_value<int, double>(local_canvas_sts, "pixel_g")) {
    pixel_g = *extract_value<int, double>(local_canvas_sts, "pixel_g");
  }
  if (extract_value<int, double>(local_canvas_sts, "pixel_b")) {
    pixel_b = *extract_value<int, double>(local_canvas_sts, "pixel_b");
  }
  if (extract_value<int, double>(local_canvas_sts, "pixel_a")) {
    pixel_a = *extract_value<int, double>(local_canvas_sts, "pixel_a");
  }
  if (extract_value<int, double>(local_canvas_sts, "to_x")) {
    to_x = *extract_value<int, double>(local_canvas_sts, "to_x");
  }
  if (extract_value<int, double>(local_canvas_sts, "to_y")) {
    to_y = *extract_value<int, double>(local_canvas_sts, "to_y");
  }
  if (extract_value<int, double>(local_canvas_sts, "from_x")) {
    from_x = *extract_value<int, double>(local_canvas_sts, "from_x");
  }
  if (extract_value<int, double>(local_canvas_sts, "from_y")) {
    from_y = *extract_value<int, double>(local_canvas_sts, "from_y");
  }
  if (extract_value<int, double>(local_canvas_sts, "thickness")) {
    thickness = *extract_value<int, double>(local_canvas_sts, "thickness");
  }

  return Line((Coord2D){to_x, to_y}, (Coord2D){from_x, from_y},
      (Pixel){pixel_r, pixel_g, pixel_b, pixel_a}, thickness);
}

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

} // namespace SLCEvaluation
