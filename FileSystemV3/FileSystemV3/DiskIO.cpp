#include <stdio.h>
#include "DiskIO.h"
#include <string.h>
#define NO_OF_BLOCKS 6400

static char HardDiskName[100] = "";
static unsigned BlockSize;
static FILE *HardDisk;

unsigned init(char *hard_disk_name, unsigned block_size) {
	strcpy(HardDiskName, hard_disk_name);
	BlockSize = block_size;
	HardDisk = fopen(HardDiskName, "rb+");

	if (HardDisk == NULL) {
		printf("Hard Disk Initialization Failed\n");
	}
	return NO_OF_BLOCKS;
}
void goto_block(unsigned block_number) {
	int check;
	check = fseek(HardDisk, block_number * BlockSize, SEEK_SET);
	if (check != 0) {
		printf("HardDisk Seeking Failed\n");
	}
}
int read_block(void *buffer, unsigned block_number) {
	goto_block(block_number);
	int test = fread(buffer, BlockSize, 1, HardDisk);
	if (test != 1) {
		return 1;
	}
	return 0;
}

int write_block(void *buffer, unsigned block_number) {
	goto_block(block_number);
	int test = fwrite(buffer, BlockSize, 1, HardDisk);
	if (test != 1) {
		return 1;
	}
	return 0;
}
int close() {
	return fclose(HardDisk);
}