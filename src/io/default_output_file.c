#include "default_output_file.h"

char default_file_name[DEFAULT_FILE_NAME_SIZE] = "`.png";

const char * get_default_file_name(void) {
  default_file_name[0]++;
  return default_file_name;
}
