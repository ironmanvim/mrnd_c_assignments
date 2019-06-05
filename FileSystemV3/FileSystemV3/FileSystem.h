#ifndef _FILE_SYSTEM_H
#define _FILE_SYSTEM_H
#include <stdio.h>

int mount(char *hard_disk, unsigned block_size);
void copy_to_disk(FILE *file, char *name);
void copy_from_disk(FILE *input_file, char *scan_filename);
void list_files();
void delete_file(char *filename);
void format();

#endif