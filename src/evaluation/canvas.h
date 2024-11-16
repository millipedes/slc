#pragma once

#include <png.h>

#include "shape_helpers.h"

namespace SLCEvaluation {

constexpr static auto max_col = 255;
constexpr static auto min_col = 0;

constexpr static auto default_canvas_pixel_r = 0;
constexpr static auto default_canvas_pixel_g = 0;
constexpr static auto default_canvas_pixel_b = 0;
constexpr static auto default_canvas_pixel_a = 255;

constexpr static auto default_canvas_height = 1000;
constexpr static auto default_canvas_width  = 1000;

struct Pixel {
  uint8_t r;
  uint8_t g;
  uint8_t b;
  uint8_t a;
  auto operator==(const Pixel& other) const -> bool;
};

struct Canvas {
  std::vector<std::vector<Pixel>> values;

  auto operator==(const Canvas& other) const -> bool;

  Canvas(const uint32_t& width, const uint32_t& height,
      const uint8_t& r, const uint8_t& g, const uint8_t& b, const uint8_t& a)
    : values(height, std::vector<Pixel>(width, Pixel{r, g, b, a})) {}
};

auto evaluate_canvas(slcp::Expr& expr, SymbolTableStack& sts) -> Canvas;

auto write_canvas_png(Canvas canvas, const char * file_name) -> void;
auto read_canvas_png(const char * file_name) -> Canvas;

} // namespace SLCEvaluation
