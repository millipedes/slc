#include "ellipse.h"

namespace SLCEvaluation {

auto Ellipse::debug() -> void {
  std::cout << "Center: " << std::endl;
  center.debug();
  std::cout << "Color: " << std::endl;
  color.debug();
  std::cout << "Major Axis: " << major_axis << std::endl;
  std::cout << "Minor Axis: " << minor_axis << std::endl;
  std::cout << "Thickness: " << thickness << std::endl;
}

auto Ellipse::operator==(const Ellipse& other) const -> bool {
  return center == other.center
    && color == other.color
    && major_axis == other.major_axis
    && minor_axis == other.minor_axis
    && thickness == other.thickness;
}

auto evaluate_ellipse(slcp::Expr expr, SymbolTableStack& sts) -> Ellipse {
  double center_x = default_ellipse_center_x;
  double center_y = default_ellipse_center_y;

  uint8_t pixel_r = default_ellipse_pixel_r;
  uint8_t pixel_g = default_ellipse_pixel_g;
  uint8_t pixel_b = default_ellipse_pixel_b;
  uint8_t pixel_a = default_ellipse_pixel_a;

  size_t major_axis = default_ellipse_major_axis;
  size_t minor_axis = default_ellipse_minor_axis;

  int thickness = default_ellipse_thickness;

  auto local_canvas_sts = std::stack<SymbolTable>();
  local_canvas_sts.push(SymbolTable());
  if (expr.child().size() > 0) {
    read_in_values(expr.child()[0], local_canvas_sts);
  }

  if (extract_value<int, double>(local_canvas_sts, "center_x")) {
    center_x = *extract_value<int, double>(local_canvas_sts, "center_x");
  }
  if (extract_value<int, double>(local_canvas_sts, "center_y")) {
    center_y = *extract_value<int, double>(local_canvas_sts, "center_y");
  }
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
  if (extract_value<int, double>(local_canvas_sts, "major_axis")) {
    major_axis = *extract_value<int, double>(local_canvas_sts, "major_axis");
  }
  if (extract_value<int, double>(local_canvas_sts, "minor_axis")) {
    minor_axis = *extract_value<int, double>(local_canvas_sts, "minor_axis");
  }
  if (extract_value<int, double>(local_canvas_sts, "thickness")) {
    thickness = *extract_value<int, double>(local_canvas_sts, "thickness");
  }

  return Ellipse(Coord2D(center_x, center_y),
      Pixel(pixel_r, pixel_g, pixel_b, pixel_a), major_axis, minor_axis, thickness);
}

// /**
//  * This function draws an ellipse.
//  * @param  the_canvas - The canvas which the ellipse will be drawn to.
//  * @param the_ellipse - The ellipse which will be written to the canvas.
//  * @return the_canvas - The canvas with the ellipse written to it.
//  */
// canvas draw_ellipse(canvas the_canvas, ellipse the_ellipse) {
//   int center_x = the_ellipse.center.x;
//   int center_y = the_ellipse.center.y;
//   int radius_x = the_ellipse.major_axis / 2;
//   int radius_y = the_ellipse.minor_axis / 2;
//   
//   int x = 0;
//   int y = radius_y;
//   int rx2 = radius_x * radius_x;
//   int ry2 = radius_y * radius_y;
//   int two_rx2 = 2 * rx2;
//   int two_ry2 = 2 * ry2;
//   int p = 0;
// 
//   // Region 1
//   int dx = 0;
//   int dy = two_rx2 * y;
// 
//   the_canvas = draw_ellipse_points(the_canvas, the_ellipse, center_x, center_y,
//       x, y);
// 
//   // Region 1
//   p = ry2 - (rx2 * radius_y) + (0.25 * rx2);
// 
//   while(dx < dy) {
//     x++;
//     dx += two_ry2;
//     if (p < 0) {
//       p += ry2 + dx;
//     } else {
//       y--;
//       dy -= two_rx2;
//       p += ry2 + dx - dy;
//     }
//     the_canvas = draw_ellipse_points(the_canvas, the_ellipse, center_x,
//         center_y, x, y);
//   }
// 
//   // Region 2
//   p = ry2 * (x + 0.5) * (x + 0.5) + rx2 * (y - 1) * (y - 1) - rx2 * ry2;
// 
//   while(y > 0) {
//     y--;
//     dy -= two_rx2;
//     if (p > 0) {
//       p += rx2 - dy;
//     } else {
//       x++;
//       dx += two_ry2;
//       p += rx2 - dy + dx;
//     }
//     the_canvas = draw_ellipse_points(the_canvas, the_ellipse, center_x,
//         center_y, x, y);
//   }
// 
//   return the_canvas;
// }
// 
// /**
//  * This function is a helper function to draw_ellipse.
//  * @param  the_canvas - The canvas which the point will be written to.
//  * @param the_ellipse - The ellipse whoe points are being written to the canvas.
//  * @param    center_x - The center x point.
//  * @param    center_y - The center y point.
//  * @param           x - The x value of the point.
//  * @param           y - The y value of the point.
//  * @return the_canvas - The canvas which will have the points written to it.
//  */
// canvas draw_ellipse_points(canvas the_canvas, ellipse the_ellipse, int center_x,
//     int center_y, int x, int y) {
//   for(int i = -the_ellipse.thickness/2; i <= the_ellipse.thickness/2; i++) {
//     for(int j = -the_ellipse.thickness/2; j <= the_ellipse.thickness/2; j++) {
//       if(center_y + y + i < the_canvas.height && center_y + y + i >= 0
//           && center_x + x + j < the_canvas.width && center_x + x + j >= 0) {
//         the_canvas.values[center_y + y + i][center_x + x + j] = the_ellipse.color;
//       }
//       if(center_y + y + i < the_canvas.height && center_y + y + i >= 0
//           && center_x - x + j < the_canvas.width && center_x - x + j >= 0) {
//         the_canvas.values[center_y + y + i][center_x - x + j] = the_ellipse.color;
//       }
//       if(center_y - y + i < the_canvas.height && center_y - y + i >= 0
//           && center_x + x + j < the_canvas.width && center_x + x + j >= 0) {
//         the_canvas.values[center_y - y + i][center_x + x + j] = the_ellipse.color;
//       }
//       if(center_y - y + i < the_canvas.height && center_y - y + i >= 0
//           && center_x - x + j < the_canvas.width && center_x - x + j >= 0) {
//         the_canvas.values[center_y - y + i][center_x - x + j] = the_ellipse.color;
//       }
//     }
//   }
//   return the_canvas;
// }
// 
// bool point_in_ellipse(ellipse the_ellipse, coord_2d point) {
//   double dx = point.x - the_ellipse.center.x;
//   double dy = point.y - the_ellipse.center.y;
// 
//   double semi_major_axis = (double)the_ellipse.major_axis / 2.0 + (double)the_ellipse.thickness;
//   double semi_minor_axis = (double)the_ellipse.minor_axis / 2.0 + (double)the_ellipse.thickness;
// 
//   double ellipse_value = (dx * dx) / (semi_major_axis * semi_major_axis) +
//     (dy * dy) / (semi_minor_axis * semi_minor_axis);
// 
//   return ellipse_value <= 1.0 + the_ellipse.thickness;
// }

} // namespace SLCEvaluation
