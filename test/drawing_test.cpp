#include "test_helper.h"

TEST(in_rectangle, in_rectangle_0) {
  ASSERT_TRUE(point_in_rectangle((rectangle){(coord_2d){0, 0}, (pixel){0, 0, 0, 0},
    5, 10, 2},
  (coord_2d){0, 0}));
}

TEST(in_rectangle, in_rectangle_1) {
  ASSERT_TRUE(point_in_rectangle((rectangle){(coord_2d){0, 0}, (pixel){0, 0, 0, 0},
    5, 10, 2},
  (coord_2d){5, 2}));
}

TEST(in_rectangle, in_rectangle_2) {
  ASSERT_FALSE(point_in_rectangle((rectangle){(coord_2d){0, 0}, (pixel){0, 0, 0, 0},
    5, 10, 2},
  (coord_2d){7, 4}));
}

TEST(in_rectangle, in_rectangle_3) {
  ASSERT_TRUE(point_in_rectangle((rectangle){(coord_2d){0, 0}, (pixel){0, 0, 0, 0},
    5, 10, 2},
  (coord_2d){5, 3}));
}

TEST(in_ellipse, in_ellipse_0) {
  ASSERT_TRUE(point_in_ellipse((ellipse){{0, 0}, (pixel){0, 0, 0, 0}, 10, 5, 2},
        (coord_2d){0, 0}));
}

TEST(in_ellipse, in_ellipse_1) {
  ASSERT_TRUE(point_in_ellipse((ellipse){{0, 0}, (pixel){0, 0, 0, 0}, 10, 5, 4},
        (coord_2d){1, 11}));
}

TEST(in_ellipse, in_ellipse_2) {
  ASSERT_TRUE(point_in_ellipse((ellipse){{0, 0}, (pixel){0, 0, 0, 0}, 10, 5, 2},
        (coord_2d){9, 1}));
}

// Here for valgrind
TEST(draw_stack, stack_0) {
  draw_stack ss = {0};
  slc_value value_one[2] = {0};
  value_one[0] = {{.the_shape = {{.the_ellipse = (ellipse){{0, 0}, (pixel){0, 0, 0, 0}, 10, 5, 2}}, ELLIPSE}}, SHAPE};
  value_one[1] = {{.the_shape = {{.the_ellipse = (ellipse){{0, 0}, (pixel){0, 0, 0, 0}, 10, 5, 2}}, ELLIPSE}}, SHAPE};
  slc_value value_two[2] = {0};
  value_two[0] = {{.the_shape = {{.the_rectangle = (rectangle){(coord_2d){0, 0}, (pixel){0, 0, 0, 0}, 5, 10, 2}}, RECTANGLE}}, SHAPE};
  value_two[1] = {{.the_shape = {{.the_rectangle = (rectangle){(coord_2d){0, 0}, (pixel){0, 0, 0, 0}, 5, 10, 2}}, RECTANGLE}}, SHAPE};
  ss = push(ss, value_one);
  ss = push(ss, value_two);
  free_draw_stack(ss);
}

TEST(line_drawing, b_curve_0) {
  canvas the_canvas = init_canvas(480, 720, 0, 0, 0, 255);
  line the_line = {(coord_2d) {0}, (coord_2d) {0}, (pixel){0, 255, 0, 255}, 5};

  points the_points = {0};
  the_points = add_point(the_points, (coord_2d){100, 100});
  the_points = add_point(the_points, (coord_2d){150, 125});
  the_points = add_point(the_points, (coord_2d){650, 150});
  the_canvas = draw_b_curve(the_canvas, the_line, the_points);
  write_canvas_png(the_canvas, "b_curve_0.png");
  free_points(the_points);
  free_canvas(the_canvas);
}

TEST(line_drawing, b_curve_1) {
  canvas the_canvas = init_canvas(480, 720, 0, 0, 0, 255);
  line the_line = {(coord_2d) {0}, (coord_2d) {0}, (pixel){0, 255, 0, 255}, 5};

  points the_points = {0};
  the_points = add_point(the_points, (coord_2d){100, 100});
  the_points = add_point(the_points, (coord_2d){10, 100});
  the_points = add_point(the_points, (coord_2d){150, 125});
  the_points = add_point(the_points, (coord_2d){650, 150});
  the_points = add_point(the_points, (coord_2d){17, 25});
  the_points = add_point(the_points, (coord_2d){701, 34});
  the_canvas = draw_b_curve(the_canvas, the_line, the_points);
  write_canvas_png(the_canvas, "b_curve_1.png");
  free_points(the_points);
  free_canvas(the_canvas);
}
