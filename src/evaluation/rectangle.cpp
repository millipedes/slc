#include "rectangle.h"

namespace SLCEvaluation {

auto Rectangle::operator==(const Rectangle& other) const -> bool {
  return center == other.center
    && color == other.color
    && height == other.height
    && width == other.width
    && thickness == other.thickness;
}

auto Rectangle::debug() -> void {
  std::cout << "Center: " << std::endl;
  center.debug();
  std::cout << "Color: " << std::endl;
  color.debug();
  std::cout << "Height: " << height << std::endl;
  std::cout << "Width: " << width << std::endl;
  std::cout << "Thickness: " << thickness << std::endl;
}

auto evaluate_rectangle(slcp::Expr& expr, SymbolTableStack& sts) -> Rectangle {
  double center_x = default_rectangle_center_x;
  double center_y = default_rectangle_center_y;

  uint8_t pixel_r = default_rectangle_pixel_r;
  uint8_t pixel_g = default_rectangle_pixel_g;
  uint8_t pixel_b = default_rectangle_pixel_b;
  uint8_t pixel_a = default_rectangle_pixel_a;

  size_t height = default_rectangle_height;
  size_t width = default_rectangle_width;

  int thickness = default_rectangle_thickness;
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
  if (extract_value<int, double>(local_canvas_sts, "height")) {
    height = *extract_value<int, double>(local_canvas_sts, "height");
  }
  if (extract_value<int, double>(local_canvas_sts, "width")) {
    width = *extract_value<int, double>(local_canvas_sts, "width");
  }

  return Rectangle(Coord2D(center_x, center_y),
    Pixel(pixel_r, pixel_g, pixel_b, pixel_a), height, width, thickness);
}

// /**
//  * This function writes a rectangle to a canvas.
//  * @param  the_canvas - The canvas for the rectangle to be drawn onto.
//  * @param    the_rect - The rectangle which will be drawn onto the cavas.
//  * @return the_canvas - The canvas with the rectangle drawn onto it.
//  */
// canvas draw_rectangle(canvas the_canvas, rectangle the_rect) {
//   int half_width = the_rect.width / 2;
//   int half_height = the_rect.height / 2;
//   double x1 = (double)(the_rect.center.x - half_width);
//   double y1 = (double)(the_rect.center.y - half_height);
//   double x2 = (double)(the_rect.center.x + half_width);
//   double y2 = (double)(the_rect.center.y + half_height);
// 
//   // Draw the four sides of the rectangle
//   draw_line(the_canvas, (line){
//       (coord_2d){x1, y1}, (coord_2d){x2, y1}, the_rect.color, the_rect.thickness});
//   draw_line(the_canvas, (line){
//       (coord_2d){x2, y1}, (coord_2d){x2, y2}, the_rect.color, the_rect.thickness});
//   draw_line(the_canvas, (line){
//       (coord_2d){x2, y2}, (coord_2d){x1, y2}, the_rect.color, the_rect.thickness});
//   draw_line(the_canvas, (line){
//       (coord_2d){x1, y2}, (coord_2d){x1, y1}, the_rect.color, the_rect.thickness});
// 
//   return the_canvas;
// }
// 
// bool point_in_rectangle(rectangle the_rect, coord_2d point) {
//   if(point.x <= (the_rect.center.x + the_rect.width / 2 + the_rect.thickness / 2)
//       && point.x >= (the_rect.center.x - the_rect.width / 2 + the_rect.thickness / 2)
//       && point.y <= (the_rect.center.y + the_rect.width / 2 + the_rect.thickness / 2)
//       && point.y >= (the_rect.center.y - the_rect.width / 2 + the_rect.thickness / 2)) {
//     return true;
//   }
//   return false;
// }

} // namespace SLCEvaluation
