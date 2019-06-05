#include "cli.h"
#include "DiskIO.h"
#include "FileSystem.h"
#include <stdio.h>

void cli_infinite() {
	while (1) {
		int command_length = 0;
		char commandString[100];
		printf("> ");
		fgets(commandString, 100, stdin);
		execute_command(commandString);
	}
}
void cli_test() {
	execute_command("INIT hard_disk.hdd 16384");
	execute_command("LS");
	close();
	getchar();
}
int main() {
	cli_infinite();
}