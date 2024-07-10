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

/**
 * This function initializes a function with dimensions heighxwidth.
 * @param      height - The height of the canvas.
 * @param       width - The width of the canvas.
 * @return the_canvas - The inited canvas.
 */
canvas init_canvas(int height, int width, uint8_t r, uint8_t g, uint8_t b) {
  canvas the_canvas = {0};
  the_canvas.height = height;
  the_canvas.width = width;
  the_canvas.values = (pixel **)calloc(height, sizeof(struct PIXEL_T **));
  for(int i = 0; i < height; i++) {
    the_canvas.values[i] = (pixel *)calloc(width, sizeof(struct PIXEL_T *));
    for(int j = 0; j < width; j++)
      the_canvas.values[i][j] = (pixel){r, g, b};
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
      PNG_COLOR_TYPE_RGB, PNG_INTERLACE_NONE, PNG_COMPRESSION_TYPE_DEFAULT,
      PNG_FILTER_TYPE_DEFAULT);
  png_write_info(png_ptr, info_ptr);
  for (int i = 0; i < the_canvas.height; i++) {
    png_bytep row = (png_byte *)calloc(the_canvas.width * 3, sizeof(png_byte));
    for(int j = 0; j < the_canvas.width; j++) {
      row[3*j + 0] = (png_byte) the_canvas.values[i][j].r;
      row[3*j + 1] = (png_byte) the_canvas.values[i][j].g;
      row[3*j + 2] = (png_byte) the_canvas.values[i][j].b;
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
      png_get_image_width(png_ptr, info_ptr), MAX_COL, MAX_COL, MAX_COL);

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
