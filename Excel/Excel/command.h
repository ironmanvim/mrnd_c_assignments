#ifndef _COMMAND_H
#define _COMMAND_H
#include "structures.h"

void commandExecuter(char **command, int command_len, Cell ***sheet, char *save, Header **header);

#endif