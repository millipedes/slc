#pragma once

#include <vector>

namespace SLCEvaluation {

static constexpr auto coord_2d_default_x = 0.0;
static constexpr auto coord_2d_default_y = 0.0;

struct Coord2D {
  double x;
  double y;
  auto operator==(const Coord2D& other) const -> bool {
    return x == other.x && y == other.y;
  }
};

using points = std::vector<Coord2D>;

} // namespace SLCEvaluation
