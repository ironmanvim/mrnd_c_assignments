#ifndef _COMPILER_H
#define _COMPILER_H
#include <stdio.h>

void process_opcode_of_file(char *filename, char *output_filename);
char **read_input(FILE *input_file, int *no_of_lines);

#endif