#include "coordinate.h"

#include <iostream>

namespace SLCEvaluation {

auto Coord2D::operator==(const Coord2D& other) const -> bool {
  return x == other.x && y == other.y;
}

auto Coord2D::debug() -> void {
  std::cout << "(x: " << x << ", y: " << y << ")" << std::endl;
}

} // namespace SLCEvaluation
