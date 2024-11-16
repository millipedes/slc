#include "line.h"

namespace SLCEvaluation {

auto Line::operator==(const Line& other) const -> bool {
  return to == other.to
    && from == other.from
    && color == other.color
    && thickness == other.thickness;
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

  auto pixel_r_it = local_canvas_sts.top().find("pixel_r");
  if (pixel_r_it != local_canvas_sts.top().end()) {
    if (std::holds_alternative<int>(local_canvas_sts.top()["pixel_r"].value())) {
      pixel_r = std::get<int>(local_canvas_sts.top()["pixel_r"].value());
    } else if (std::holds_alternative<double>(local_canvas_sts.top()["pixel_r"].value())) {
      pixel_r = std::get<double>(local_canvas_sts.top()["pixel_r"].value());
    }
  }
  auto pixel_g_it = local_canvas_sts.top().find("pixel_g");
  if (pixel_g_it != local_canvas_sts.top().end()) {
    if (std::holds_alternative<int>(local_canvas_sts.top()["pixel_g"].value())) {
      pixel_g = std::get<int>(local_canvas_sts.top()["pixel_g"].value());
    } else if (std::holds_alternative<double>(local_canvas_sts.top()["pixel_g"].value())) {
      pixel_g = std::get<double>(local_canvas_sts.top()["pixel_g"].value());
    }
  }
  auto pixel_b_it = local_canvas_sts.top().find("pixel_b");
  if (pixel_b_it != local_canvas_sts.top().end()) {
    if (std::holds_alternative<int>(local_canvas_sts.top()["pixel_b"].value())) {
      pixel_b = std::get<int>(local_canvas_sts.top()["pixel_b"].value());
    } else if (std::holds_alternative<double>(local_canvas_sts.top()["pixel_b"].value())) {
      pixel_b = std::get<double>(local_canvas_sts.top()["pixel_b"].value());
    }
  }
  auto pixel_a_it = local_canvas_sts.top().find("pixel_a");
  if (pixel_a_it != local_canvas_sts.top().end()) {
    if (std::holds_alternative<int>(local_canvas_sts.top()["pixel_a"].value())) {
      pixel_a = std::get<int>(local_canvas_sts.top()["pixel_a"].value());
    } else if (std::holds_alternative<double>(local_canvas_sts.top()["pixel_a"].value())) {
      pixel_a = std::get<double>(local_canvas_sts.top()["pixel_a"].value());
    }
  }
  auto to_x_it = local_canvas_sts.top().find("to_x");
  if (to_x_it != local_canvas_sts.top().end()) {
    if (std::holds_alternative<int>(local_canvas_sts.top()["to_x"].value())) {
      to_x = std::get<int>(local_canvas_sts.top()["to_x"].value());
    } else if (std::holds_alternative<double>(local_canvas_sts.top()["to_x"].value())) {
      to_x = std::get<double>(local_canvas_sts.top()["to_x"].value());
    }
  }
  auto to_y_it = local_canvas_sts.top().find("to_y");
  if (to_y_it != local_canvas_sts.top().end()) {
    if (std::holds_alternative<int>(local_canvas_sts.top()["to_y"].value())) {
      to_y = std::get<int>(local_canvas_sts.top()["to_y"].value());
    } else if (std::holds_alternative<double>(local_canvas_sts.top()["to_y"].value())) {
      to_y = std::get<double>(local_canvas_sts.top()["to_y"].value());
    }
  }
  auto from_x_it = local_canvas_sts.top().find("from_x");
  if (from_x_it != local_canvas_sts.top().end()) {
    if (std::holds_alternative<int>(local_canvas_sts.top()["from_x"].value())) {
      from_x = std::get<int>(local_canvas_sts.top()["from_x"].value());
    } else if (std::holds_alternative<double>(local_canvas_sts.top()["from_x"].value())) {
      from_x = std::get<double>(local_canvas_sts.top()["from_x"].value());
    }
  }
  auto from_y_it = local_canvas_sts.top().find("from_y");
  if (from_y_it != local_canvas_sts.top().end()) {
    if (std::holds_alternative<int>(local_canvas_sts.top()["from_y"].value())) {
      from_y = std::get<int>(local_canvas_sts.top()["from_y"].value());
    } else if (std::holds_alternative<double>(local_canvas_sts.top()["from_y"].value())) {
      from_y = std::get<double>(local_canvas_sts.top()["from_y"].value());
    }
  }
  auto thickness_it = local_canvas_sts.top().find("thickness");
  if (thickness_it != local_canvas_sts.top().end()) {
    if (std::holds_alternative<int>(local_canvas_sts.top()["thickness"].value())) {
      thickness = std::get<int>(local_canvas_sts.top()["thickness"].value());
    } else if (std::holds_alternative<double>(local_canvas_sts.top()["thickness"].value())) {
      thickness = std::get<double>(local_canvas_sts.top()["thickness"].value());
    }
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
