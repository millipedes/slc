#include "evaluation.h"

points deep_copy_points(points original) {
  points result = {0};
  result.qty_points = original.qty_points;
  result.value = (coord_2d *)calloc(original.qty_points, sizeof(struct COORD2D_T));
  for(uint32_t i = 0; i < original.qty_points; i++) {
    result.value[i].x = original.value[i].x;
    result.value[i].y = original.value[i].y;
  }
  return result;
}

points add_point(points the_points, coord_2d addition) {
  the_points.qty_points++;
  if(the_points.value) {
    the_points.value = (coord_2d *)realloc(the_points.value,
        the_points.qty_points * sizeof(struct COORD2D_T));
  } else {
    the_points.value = (coord_2d *)calloc(1, sizeof(struct COORD2D_T));
  }
  the_points.value[the_points.qty_points - 1] = addition;
  return the_points;
}

void free_points(points the_points) {
  if(the_points.value) {
    free(the_points.value);
  }
}
