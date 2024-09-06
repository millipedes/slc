// #include "read_evaluate_file.h"
// 
// int read_evaluate_file(const char * file_name) {
//   FILE * fp = fopen(file_name, "r");
//   if(!fp) {
//     fprintf(stderr, "[READ_EVALUATE_FILE]: could not open file\n");
//     return 1;
//   }
// 
//   fseek(fp, 0, SEEK_END);
//   long fp_size = ftell(fp);
//   fseek(fp, 0, SEEK_SET);
// 
//   char * input = (char *)calloc(fp_size + 1, sizeof(char));
//   size_t read_size = fread(input, 1, fp_size, fp);
//   input[fp_size] = '\0';
// 
//   parsed_lline the_lline = {0};
//   symbol_table st = {0};
//   const char * remainder = input;
//   while(remainder[0] != '\0') {
//     remainder = parse_lline(remainder, &the_lline);
//     remainder = parse_ws(remainder);
//     evaluate_lline(the_lline, &st);
//     free_parsed_lline(the_lline);
//     the_lline = (parsed_lline){0};
//   }
// 
//   free_symbol_table(st);
//   free(input);
//   fclose(fp);
//   return 0;
// }
