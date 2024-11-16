#pragma once

#include "line.h"

namespace SLCEvaluation {

constexpr static auto default_rectangle_center_x  = 0;
constexpr static auto default_rectangle_center_y  = 0;
constexpr static auto default_rectangle_pixel_r   = 0;
constexpr static auto default_rectangle_pixel_g   = 0;
constexpr static auto default_rectangle_pixel_b   = 0;
constexpr static auto default_rectangle_pixel_a   = 255;
constexpr static auto default_rectangle_height    = 100;
constexpr static auto default_rectangle_width     = 100;
constexpr static auto default_rectangle_thickness = 10;

struct Rectangle {
  Coord2D center;
  Pixel color;
  size_t height;
  size_t width;
  int thickness;

  auto operator==(const Rectangle& other) const -> bool;
  auto debug() -> void;

  Rectangle(const Coord2D& center, const Pixel& color, const size_t height,
      const size_t width, const int thickness)
    : center(center), color(color), height(height), width(width), thickness(thickness) {}
};

auto evaluate_rectangle(slcp::Expr& expr, SymbolTableStack& sts) -> Rectangle;
// canvas draw_rectangle(canvas the_canvas, rectangle the_rect);
// bool point_in_rectangle(rectangle the_rect, coord_2d point);

} // namespace SLCEvaluation
