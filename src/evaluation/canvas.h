// #pragma once
// 
// #include <png.h>
// 
// #include "../parsing/parsing_ds.h"
// #include "symbol_table.h"
// 
// namespace slcp = SLCParsing;
// 
// namespace SLCEvaluation {
// 
// constexpr static auto max_col = 255;
// constexpr static auto min_col = 0;
// 
// constexpr static auto default_canvas_pixel_r = 0;
// constexpr static auto default_canvas_pixel_g = 0;
// constexpr static auto default_canvas_pixel_b = 0;
// constexpr static auto default_canvas_pixel_a = 255;
// 
// constexpr static auto default_canvas_height = 1000;
// constexpr static auto default_canvas_width  = 1000;
// 
// struct pixel {
//   uint8_t r;
//   uint8_t g;
//   uint8_t b;
//   uint8_t a;
// };
// 
// typedef struct CANVAS_T {
//   std::vector<std::vector<pixel>> values;
// } canvas;
// 
// auto evaluate_canvas(slcp::Expr::expr, SymbolTableStack& st) -> canvas;
// 
// // canvas deep_copy_canvas(canvas original);
// // canvas init_canvas(int height, int width, uint8_t r, uint8_t g, uint8_t b, uint8_t a);
// // void write_canvas_png(canvas the_canvas, const char * file_name);
// // canvas read_canvas_png(const char *file_name);
// // void free_canvas(canvas the_canvas);
// 
// extern auto opaque_eval_expr(slcp::Expr& value, SymbolTableStack& sts) -> slcp::Expr;
// 
// } // namespace SLCEvaluation
