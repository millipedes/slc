/**
 * @file   canvas.c
 * @brief  This file contains the functions related to the canvas data
 * structure.
 * @author Matthew C. Lindeman
 * @date   January 30, 2024
 * @bug    None known
 * @todo   Nothing
 */
#include "canvas.h"

canvas evaluate_canvas(parsed_shape the_shape, symbol_table * st) {
  uint8_t pixel_r = DEFAULT_CANVAS_PIXEL_R;
  uint8_t pixel_g = DEFAULT_CANVAS_PIXEL_G;
  uint8_t pixel_b = DEFAULT_CANVAS_PIXEL_B;
  uint8_t pixel_a = DEFAULT_CANVAS_PIXEL_A;

  size_t height = DEFAULT_CANVAS_HEIGHT;
  size_t width = DEFAULT_CANVAS_WIDTH;

  expression tmp_name = {0};
  expression tmp_value = {0};

  for(uint32_t i = 0; i < the_shape.qty_values; i++) {
    tmp_name = the_shape.values[i];
    i++;
    tmp_value = opaque_eval_expr(&the_shape.values[i], st);
    validate_type(tmp_name, VAR, "[EVALUATE_CANVAS]: name was not specified before value\n");

    if(!strncmp(tmp_name.value.string_value, "pixel_r", sizeof("pixel_r") - 1)) {
      validate_type(tmp_value, INT, "[EVALUATE_CANVAS]: pixel_r requires an int\n");
      pixel_r = (uint8_t)tmp_value.value.int_value;
    } else if(!strncmp(tmp_name.value.string_value, "pixel_g", sizeof("pixel_g") - 1)) {
      validate_type(tmp_value, INT, "[EVALUATE_CANVAS]: pixel_g requires an int\n");
      pixel_g = (uint8_t)tmp_value.value.int_value;
    } else if(!strncmp(tmp_name.value.string_value, "pixel_b", sizeof("pixel_b") - 1)) {
      validate_type(tmp_value, INT, "[EVALUATE_CANVAS]: pixel_b requires an int\n");
      pixel_b = (uint8_t)tmp_value.value.int_value;
    } else if(!strncmp(tmp_name.value.string_value, "pixel_a", sizeof("pixel_a") - 1)) {
      validate_type(tmp_value, INT, "[EVALUATE_CANVAS]: pixel_a requires an int\n");
      pixel_a = (uint8_t)tmp_value.value.int_value;
    } else if(!strncmp(tmp_name.value.string_value, "height", sizeof("height") - 1)) {
      validate_type(tmp_value, INT, "[EVALUATE_CANVAS]: height requires a int\n");
      height = (size_t)tmp_value.value.int_value;
    } else if(!strncmp(tmp_name.value.string_value, "width", sizeof("width") - 1)) {
      validate_type(tmp_value, INT, "[EVALUATE_CANVAS]: width requires a int\n");
      width = (size_t)tmp_value.value.int_value;
    } else {
      fprintf(stderr, "[EVALUATE_CANVAS]: unrecognized directive `%s`\n",
          tmp_name.value.string_value);
      exit(1);
    }

    tmp_name = (expression){0};
    tmp_value = (expression){0};
  }
  return init_canvas(height, width, pixel_r, pixel_g, pixel_b, pixel_a);
}

canvas deep_copy_canvas(canvas original) {
  canvas copy = {0};
  copy.height = original.height;
  copy.width = original.width;
  copy.values = (pixel **)calloc(original.width, sizeof(struct PIXEL_T *));
  for(int i = 0; i < copy.height; i++) {
    copy.values[i] = (pixel *)calloc(original.width, sizeof(struct PIXEL_T));
    for(int j = 0; j < copy.width; j++) {
      copy.values[i][j].r = original.values[i][j].r;
      copy.values[i][j].g = original.values[i][j].g;
      copy.values[i][j].b = original.values[i][j].b;
      copy.values[i][j].a = original.values[i][j].a;
    }
  }
  return copy;
}

/**
 * This function initializes a function with dimensions heighxwidth.
 * @param      height - The height of the canvas.
 * @param       width - The width of the canvas.
 * @return the_canvas - The inited canvas.
 */
canvas init_canvas(int height, int width, uint8_t r, uint8_t g, uint8_t b, uint8_t a) {
  canvas the_canvas = {0};
  the_canvas.height = height;
  the_canvas.width = width;
  the_canvas.values = (pixel **)calloc(height, sizeof(struct PIXEL_T *));
  for(int i = 0; i < height; i++) {
    the_canvas.values[i] = (pixel *)calloc(width, sizeof(struct PIXEL_T));
    for(int j = 0; j < width; j++)
      the_canvas.values[i][j] = (pixel){r, g, b, a};
  }
  return the_canvas;
}

/**
  * This function writes a canvas to a png file.
  * @param the_canvas - The canvas to be written to the png file.
  * @param  file_name - The name of the file which it will write to.
  * @return       N/a
  */
void write_canvas_png(canvas the_canvas, const char * file_name) {
  FILE * fp = fopen(file_name, "w");
  png_structp png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING,
      NULL, NULL, NULL);
  png_infop info_ptr = png_create_info_struct(png_ptr);
  png_init_io(png_ptr, fp);
  png_set_IHDR(png_ptr, info_ptr, the_canvas.width, the_canvas.height, 8,
      PNG_COLOR_TYPE_RGBA, PNG_INTERLACE_NONE, PNG_COMPRESSION_TYPE_DEFAULT,
      PNG_FILTER_TYPE_DEFAULT);
  png_write_info(png_ptr, info_ptr);
  for (int i = 0; i < the_canvas.height; i++) {
    png_bytep row = (png_byte *)calloc(the_canvas.width * 4, sizeof(png_byte));
    for(int j = 0; j < the_canvas.width; j++) {
      row[4*j + 0] = (png_byte) the_canvas.values[i][j].r;
      row[4*j + 1] = (png_byte) the_canvas.values[i][j].g;
      row[4*j + 2] = (png_byte) the_canvas.values[i][j].b;
      row[4*j + 3] = (png_byte) the_canvas.values[i][j].a;
    }
    png_write_row(png_ptr, row);
    free(row);
    row = NULL;
  }

  png_write_end(png_ptr, info_ptr);
  png_destroy_write_struct(&png_ptr, &info_ptr);
  fclose(fp);
}

/**
 * This function reads a png file into a canvas.
 * @param   file_name - The name of the netpbm file.
 * @return the_canvas - The canvas the file was written to.
 */
canvas read_canvas_png(const char *file_name) {
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

  canvas the_canvas = init_canvas(png_get_image_height(png_ptr, info_ptr),
      png_get_image_width(png_ptr, info_ptr), MAX_COL, MAX_COL, MAX_COL, MAX_COL);

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

  for (int i = 0; i < the_canvas.height; i++) {
    png_bytep row = (png_bytep)malloc(png_get_rowbytes(png_ptr, info_ptr));
    png_read_row(png_ptr, row, NULL);

    for (int j = 0; j < the_canvas.width; j++) {
      the_canvas.values[i][j].r = (int)row[3 * j];
      the_canvas.values[i][j].g = (int)row[3 * j + 1];
      the_canvas.values[i][j].b = (int)row[3 * j + 2];
      the_canvas.values[i][j].a = 255;
    }

    free(row);
  }

  fclose(fp);
  png_destroy_read_struct(&png_ptr, &info_ptr, NULL);
  return the_canvas;
}

/**
 * This function frees a canvas.
 * @param the_canvas - The canvas to be freed.
 * @return       N/a
 */
void free_canvas(canvas the_canvas) {
  if(the_canvas.values) {
    for(int i = 0; i < the_canvas.height; i++) {
      free(the_canvas.values[i]);
    }
    free(the_canvas.values);
  }
}
