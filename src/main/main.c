#include "io/read_evaluate_file.h"

int main(int argc, char * argv[]) {
  if(argc != 2) {
    fprintf(stderr, "slc expects at least one input file\n");
    exit(1);
  }
  return read_evaluate_file(argv[1]);
}
