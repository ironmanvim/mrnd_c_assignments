#include <stdlib.h>
#include <stdio.h>
#include "command.h"
#include "tokenizer.h"
#include "structures.h"


void createSheetAndExecute() {
	Cell ***sheet = (Cell ***)malloc(sizeof(Cell **) * 10);
	for (int i = 0; i < 10; i++) {
		sheet[i] = (Cell **)malloc(sizeof(Cell *) * 10);
		for (int j = 0; j < 10; j++) {
			sheet[i][j] = createCell("0", INTEGER);
		}
	}
	Header **header = (Header **)malloc(sizeof(Header *) * 10);
	for (int i = 0; i < 10; i++) {
		header[i] = createHeader(NULL, INTEGER);
	}
	char save[100] = "";
	while (1) {
		int command_length = 0;
		char commandString[100];
		printf("> ");
		fgets(commandString, 100, stdin);
		char **command = tokenize(commandString, &command_length);
		commandExecuter(command, command_length, sheet, save, header);
	}
}