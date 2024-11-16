#pragma once

#include "canvas.h"
#include "coordinate.h"
#include "shape_helpers.h"

namespace SLCEvaluation {

constexpr static auto default_ellipse_center_x   = 0;
constexpr static auto default_ellipse_center_y   = 0;

constexpr static auto default_ellipse_pixel_r    = 0;
constexpr static auto default_ellipse_pixel_g    = 0;
constexpr static auto default_ellipse_pixel_b    = 0;
constexpr static auto default_ellipse_pixel_a    = 255;

constexpr static auto default_ellipse_major_axis = 100;
constexpr static auto default_ellipse_minor_axis = 100;

constexpr static auto default_ellipse_thickness  = 10;

struct Ellipse {
  Coord2D center;
  Pixel color;
  size_t major_axis;
  size_t minor_axis;
  int thickness;

  auto operator==(const Ellipse& other) const -> bool;
  auto debug() -> void;

  Ellipse(const Coord2D& center, const Pixel& color, const size_t& major_axis, const size_t& minor_axis, const int& thickness) : center(center), color(color), major_axis(major_axis), minor_axis(minor_axis), thickness(thickness) {}
};

auto evaluate_ellipse(slcp::Expr expr, SymbolTableStack& sts) -> Ellipse;
// canvas draw_ellipse(canvas the_canvas, ellipse the_ellipse);
// canvas draw_ellipse_points(canvas the_canvas, ellipse the_ellipse, int center_x,
//     int center_y, int x, int y);
// bool point_in_ellipse(ellipse the_ellipse, coord_2d point);

} // namespace SLCEvaluation
