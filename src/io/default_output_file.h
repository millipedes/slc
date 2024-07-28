#ifndef DEFAULT_OUTPUT_FILE_H
#define DEFAULT_OUTPUT_FILE_H

#define DEFAULT_FILE_NAME_SIZE sizeof("`.png")

extern char default_file_name[DEFAULT_FILE_NAME_SIZE];

const char * get_default_file_name(void);

#endif
