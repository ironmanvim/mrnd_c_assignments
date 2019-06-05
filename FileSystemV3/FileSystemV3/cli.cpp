#include <stdio.h>
#include "DiskIO.h"
#include "cli.h"
#include "tokenizer.h"
#include "FileSystem.h"
#include <string.h>
#include <stdlib.h>

void execute_command(char *command) {
	int command_tokens_len = 0;
	char **command_tokens = tokenize(command, &command_tokens_len);
	command_tokens[0] = _strupr(command_tokens[0]);

	if (!strcmp(command_tokens[0], "INIT")) {
		mount(command_tokens[1], atoi(command_tokens[2]));
	}
	else if (!strcmp(command_tokens[0], "COPYTOFS")) {
		FILE *input_file = fopen(command_tokens[1], "rb");
		if (input_file == NULL) {
			return;
		}
		copy_to_disk(input_file, command_tokens[2]);
		fclose(input_file);
	}
	else if (!strcmp(command_tokens[0], "COPYFROMFS")) {
		FILE *input_file = fopen(command_tokens[2], "wb");
		if (input_file == NULL) {
			return;
		}
		copy_from_disk(input_file, command_tokens[1]);
		fclose(input_file);
	}
	else if (!strcmp(command_tokens[0], "FORMAT")) {
		format();
	}
	else if (!strcmp(command_tokens[0], "LS")) {
		list_files();
	}
	else if (!strcmp(command_tokens[0], "DELETE")) {
		delete_file(command_tokens[1]);
	}
	else if(!strcmp(command_tokens[0], "DEBUG")) {

	}
	else if(!strcmp(command_tokens[0], "EXIT")) {
		close();
		exit(0);
	}
}
