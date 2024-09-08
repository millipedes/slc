// #pragma once
// 
// #include "canvas.h"
// #include "coordinate.h"
// #include "symbol_table.h"
// 
// namespace slcp = SLCParsing;
// 
// namespace SLCEvaluation {
// 
// constexpr static auto default_line_to_x = 0;
// constexpr static auto default_line_to_y = 0;
// 
// constexpr static auto default_line_from_x = 100;
// constexpr static auto default_line_from_y = 100;
// 
// constexpr static auto default_line_pixel_r = 0;
// constexpr static auto default_line_pixel_g = 0;
// constexpr static auto default_line_pixel_b = 0;
// constexpr static auto default_line_pixel_a = 255;
// 
// constexpr static auto default_line_thickness = 10;
// 
// constexpr static auto b_curve_delta = 0.0001;
// 
// struct line {
//   coord_2d to;
//   coord_2d from;
//   pixel color;
//   int thickness;
// };
// 
// auto evaluate_line(slcp::Expr& expr, SymbolTableStack& sts) -> line;
// // canvas draw_line(canvas the_canvas, line the_line);
// // 
// // canvas draw_b_curve(canvas the_canvas, line the_line, points the_points);
// // coord_2d de_casteljau(points the_points, double t);
// 
// extern auto opaque_eval_expr(slcp::Expr& value, SymbolTableStack& sts) -> slcp::Expr;
// 
// } // namespace SLCEvaluation
