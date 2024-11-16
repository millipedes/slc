#include "canvas.h"

namespace SLCEvaluation {

auto Pixel::operator==(const Pixel& other) const -> bool {
  return r == other.r
    && g == other.g
    && b == other.b
    && a == other.a;
}

auto Canvas::operator==(const Canvas& other) const -> bool {
  return values == other.values;
}

auto evaluate_canvas(slcp::Expr& expr, SymbolTableStack& sts) -> Canvas {
  uint8_t pixel_r = default_canvas_pixel_r;
  uint8_t pixel_g = default_canvas_pixel_g;
  uint8_t pixel_b = default_canvas_pixel_b;
  uint8_t pixel_a = default_canvas_pixel_a;

  uint32_t height = default_canvas_height;
  uint32_t width = default_canvas_width;

  auto local_canvas_sts = std::stack<SymbolTable>();
  local_canvas_sts.push(SymbolTable());
  read_in_values(expr.child()[0], local_canvas_sts);

  auto pixel_r_it = local_canvas_sts.top().find("pixel_r");
  if (pixel_r_it != local_canvas_sts.top().end()) {
    if (std::holds_alternative<int>(local_canvas_sts.top()["pixel_r"].value())) {
      pixel_r = std::get<int>(local_canvas_sts.top()["pixel_r"].value());
    } else if (std::holds_alternative<double>(local_canvas_sts.top()["pixel_r"].value())) {
      pixel_r = std::get<double>(local_canvas_sts.top()["pixel_r"].value());
    }
  }
  auto pixel_g_it = local_canvas_sts.top().find("pixel_g");
  if (pixel_g_it != local_canvas_sts.top().end()) {
    if (std::holds_alternative<int>(local_canvas_sts.top()["pixel_g"].value())) {
      pixel_g = std::get<int>(local_canvas_sts.top()["pixel_g"].value());
    } else if (std::holds_alternative<double>(local_canvas_sts.top()["pixel_g"].value())) {
      pixel_g = std::get<double>(local_canvas_sts.top()["pixel_g"].value());
    }
  }
  auto pixel_b_it = local_canvas_sts.top().find("pixel_b");
  if (pixel_b_it != local_canvas_sts.top().end()) {
    if (std::holds_alternative<int>(local_canvas_sts.top()["pixel_b"].value())) {
      pixel_b = std::get<int>(local_canvas_sts.top()["pixel_b"].value());
    } else if (std::holds_alternative<double>(local_canvas_sts.top()["pixel_b"].value())) {
      pixel_b = std::get<double>(local_canvas_sts.top()["pixel_b"].value());
    }
  }
  auto pixel_a_it = local_canvas_sts.top().find("pixel_a");
  if (pixel_a_it != local_canvas_sts.top().end()) {
    if (std::holds_alternative<int>(local_canvas_sts.top()["pixel_a"].value())) {
      pixel_a = std::get<int>(local_canvas_sts.top()["pixel_a"].value());
    } else if (std::holds_alternative<double>(local_canvas_sts.top()["pixel_a"].value())) {
      pixel_a = std::get<double>(local_canvas_sts.top()["pixel_a"].value());
    }
  }
  auto height_it = local_canvas_sts.top().find("height");
  if (height_it != local_canvas_sts.top().end()) {
    if (std::holds_alternative<int>(local_canvas_sts.top()["height"].value())) {
      height = std::get<int>(local_canvas_sts.top()["height"].value());
    } else if (std::holds_alternative<double>(local_canvas_sts.top()["height"].value())) {
      height = std::get<double>(local_canvas_sts.top()["height"].value());
    }
  }
  auto width_it = local_canvas_sts.top().find("width");
  if (width_it != local_canvas_sts.top().end()) {
    if (std::holds_alternative<int>(local_canvas_sts.top()["width"].value())) {
      width = std::get<int>(local_canvas_sts.top()["width"].value());
    } else if (std::holds_alternative<double>(local_canvas_sts.top()["width"].value())) {
      width = std::get<double>(local_canvas_sts.top()["width"].value());
    }
  }
  return Canvas(width, height, pixel_r, pixel_g, pixel_b, pixel_a);
}

auto write_canvas_png(Canvas canvas, const char * file_name) -> void {
  FILE * fp = fopen(file_name, "w");
  png_structp png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING,
      NULL, NULL, NULL);
  png_infop info_ptr = png_create_info_struct(png_ptr);
  png_init_io(png_ptr, fp);
  png_set_IHDR(png_ptr, info_ptr, canvas.values[0].size(), canvas.values.size(), 8,
      PNG_COLOR_TYPE_RGBA, PNG_INTERLACE_NONE, PNG_COMPRESSION_TYPE_DEFAULT,
      PNG_FILTER_TYPE_DEFAULT);
  png_write_info(png_ptr, info_ptr);
  for (int i = 0; i < canvas.values.size(); i++) {
    png_bytep row = (png_byte *)calloc(canvas.values[0].size() * 4, sizeof(png_byte));
    for(int j = 0; j < canvas.values[0].size(); j++) {
      row[4*j + 0] = (png_byte) canvas.values[i][j].r;
      row[4*j + 1] = (png_byte) canvas.values[i][j].g;
      row[4*j + 2] = (png_byte) canvas.values[i][j].b;
      row[4*j + 3] = (png_byte) canvas.values[i][j].a;
    }
    png_write_row(png_ptr, row);
    free(row);
    row = NULL;
  }

  png_write_end(png_ptr, info_ptr);
  png_destroy_write_struct(&png_ptr, &info_ptr);
  fclose(fp);
}

auto read_canvas_png(const char * file_name) -> Canvas {
  FILE *fp = fopen(file_name, "r");

  png_byte header[8];
  if(!fread(header, 1, 8, fp)) {
    fprintf(stderr, "[READ_CANVAS_PNG]: fread error\nExiting\n");
    exit(1);
  }
  png_sig_cmp(header, 0, 8);

  png_structp png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
  png_infop info_ptr = png_create_info_struct(png_ptr);

  png_init_io(png_ptr, fp);
  png_set_sig_bytes(png_ptr, 8);

  png_read_info(png_ptr, info_ptr);

  Canvas canvas = Canvas(png_get_image_width(png_ptr, info_ptr),
      png_get_image_height(png_ptr, info_ptr), min_col, min_col, min_col, max_col);
      

  png_byte color_type = png_get_color_type(png_ptr, info_ptr);
  png_byte bit_depth = png_get_bit_depth(png_ptr, info_ptr);

  if(bit_depth == 16)
    png_set_strip_16(png_ptr);
  if(color_type == PNG_COLOR_TYPE_PALETTE)
    png_set_palette_to_rgb(png_ptr);
  if(color_type == PNG_COLOR_TYPE_GRAY && bit_depth < 8)
    png_set_expand_gray_1_2_4_to_8(png_ptr);
  if(png_get_valid(png_ptr, info_ptr, PNG_INFO_tRNS))
    png_set_tRNS_to_alpha(png_ptr);

  png_read_update_info(png_ptr, info_ptr);

  for (int i = 0; i < canvas.values.size(); i++) {
    png_bytep row = (png_bytep)malloc(png_get_rowbytes(png_ptr, info_ptr));
    png_read_row(png_ptr, row, NULL);

    for (int j = 0; j < canvas.values[0].size(); j++) {
      canvas.values[i][j].r = (int)row[3 * j];
      canvas.values[i][j].g = (int)row[3 * j + 1];
      canvas.values[i][j].b = (int)row[3 * j + 2];
      canvas.values[i][j].a = 255;
    }

    free(row);
  }

  fclose(fp);
  png_destroy_read_struct(&png_ptr, &info_ptr, NULL);
  return canvas;
}

} // namespace SLCEvaluation
