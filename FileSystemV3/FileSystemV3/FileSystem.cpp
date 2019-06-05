#include "DiskIO.h"
#include "FileSystem.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAGIC_NUMBER 0x444E524D
#define BLOCK_SIZE (16 * 1024)
#define NO_OF_BLOCKS 6400
#define FILES_START_FROM_BLOCK 4
#define METADATA_BLOCKS 4
#define MAX_FILES 32
#define LEAVE_START_BYTES 4 * 1024
#define MAX_META_ROW_SIZE 32

struct MetaFileInfo {
	char name[20];
	unsigned start_block;
	unsigned no_of_blocks;
	unsigned file_size;
};
struct MetaData {
	unsigned magic_number;
	MetaFileInfo files[32];
	char no_of_files;
	int bits[NO_OF_BLOCKS];
};
typedef struct MetaFileInfo MetaFileInfo;
typedef struct MetaData MetaData;

static char HardDiskName[20];
static unsigned BlockSize;

int mount(char *hard_disk, unsigned block_size) {
	strcpy(HardDiskName, hard_disk);
	BlockSize = block_size;
	int no_of_blocks = init(hard_disk, BlockSize);

	void *buffer = malloc(sizeof(MetaData));
	MetaData metadata;
	read_block(buffer, 0);
	memcpy(&metadata, buffer, sizeof(MetaData));
	if (metadata.magic_number != MAGIC_NUMBER) {
		metadata.magic_number = MAGIC_NUMBER;
		metadata.no_of_files = 0;
		memset(metadata.bits, 0, NO_OF_BLOCKS*sizeof(int));
		write_block(&metadata, 0);
	}
	return 1;
}
void read_file_to_buffer(void *buffer, FILE *file, unsigned size) {
	memset(buffer, 0, BLOCK_SIZE);
	fread(buffer, size, 1, file);
}
void write_buffer_to_file(void *buffer, FILE *file, unsigned size) {
	fwrite(buffer, size, 1, file);
}
void read_buffer_from_disk(void *buffer, unsigned block_number) {
	memset(buffer, 0, BLOCK_SIZE);
	read_block(buffer, block_number);
}
void write_buffer_to_disk(void *buffer, unsigned block_number) {
	write_block(buffer, block_number);
}
MetaData *get_metadata() {
	void *buffer = malloc(BLOCK_SIZE);
	read_buffer_from_disk(buffer, 0);
	MetaData *metadata = (MetaData *)malloc(sizeof(MetaData));
	memcpy(metadata, buffer, sizeof(MetaData));
	return metadata;
}
unsigned get_file_size(FILE *file) {
	int check;
	check = fseek(file, 0, SEEK_END);
	if (check != 0) {
		printf("Error in Finding File Size\n");
		return 0;
	}
	return ftell(file);
}
unsigned get_free_block(int *bits) {
	for (int i = 4; i < BLOCK_SIZE; i++) {
		if (bits[i] == 0) {
			return i;
		}
	}
	printf("No Blocks Remaining\n");
	return 0;
}
void update_metadata(MetaData *metadata) {
	write_block(metadata, 0);
}
void format() {
	MetaData metadata;
	metadata.no_of_files = 0;
	metadata.magic_number = 0x444E524D;
	memset(metadata.bits, 0, NO_OF_BLOCKS);
	write_block(&metadata, 0);
}
void delete_file(char *filename) {
	MetaData *metadata = get_metadata();
	int no_of_files = metadata->no_of_files;
	int start_block = -1;
	int i;
	for (i = 0; i < no_of_files; i++) {
		if (!strcmp(filename, metadata->files[i].name)) {
			start_block = metadata->files[i].start_block;
			break;
		}
	}
	if (i == metadata->no_of_files) {
		printf("File not found\n");
		return;
	}
	else {
		unsigned count = 0;
		unsigned *block_array = (unsigned *)malloc(BLOCK_SIZE);
		read_block(block_array, start_block);
		for (int j = 0; count < metadata->files[i].no_of_blocks; count++, j++) {
			metadata->bits[block_array[j]] = 0;
		}
		if (i < no_of_files - 1) {
			metadata->files[i].file_size = metadata->files[no_of_files - 1].file_size;
			strcpy(metadata->files[i].name, metadata->files[no_of_files - 1].name);
			metadata->files[i].no_of_blocks = metadata->files[no_of_files - 1].no_of_blocks;
			metadata->files[i].start_block = metadata->files[no_of_files - 1].start_block;
		}
		metadata->no_of_files--;
		write_block(&metadata, 0);
	}
}
void list_files() {
	MetaData *metadata = get_metadata();
	for (int i = 0; i < metadata->no_of_files; i++) {
		printf("%s\n", metadata->files[i].name);
	}
}
void copy_to_disk(FILE *file, char *name) {
	MetaData *metadata = get_metadata();

	unsigned no_of_files = metadata->no_of_files;
	unsigned file_size = get_file_size(file);
	char filename[32] = "";
	strcpy(filename, name);
	unsigned start_block = get_free_block(metadata->bits);
	metadata->no_of_files++;
	metadata->files[no_of_files].file_size = file_size;
	metadata->files[no_of_files].start_block = start_block;
	metadata->files[no_of_files].no_of_blocks = file_size / BLOCK_SIZE + 1;
	metadata->bits[start_block] = 1;
	strcpy(metadata->files[no_of_files].name, filename);

	rewind(file);
	unsigned *block_array = (unsigned *)malloc(BLOCK_SIZE);
	int k = 0;
	void *file_buffer = malloc(BLOCK_SIZE);
	int test;
	if (file_size >= BLOCK_SIZE) {
		while (file_size >= BLOCK_SIZE) {
			block_array[k] = get_free_block(metadata->bits);
			read_file_to_buffer(file_buffer, file, BLOCK_SIZE);
			write_buffer_to_disk(file_buffer, block_array[k]);
			metadata->bits[block_array[k]] = 1;
			file_size -= BLOCK_SIZE;
			k++;
		}
		block_array[k] = get_free_block(metadata->bits);
		read_file_to_buffer(file_buffer, file, BLOCK_SIZE);
		write_buffer_to_disk(file_buffer, block_array[k]);
		metadata->bits[block_array[k]] = 1;
		write_buffer_to_disk(block_array, start_block);
	}
	else {
		test = fread(file_buffer, file_size, 1, file);
		write_block(file_buffer, start_block);
		metadata->bits[start_block] = 1;
	}
	update_metadata(metadata);
}

void copy_from_disk(FILE *input_file, char *scan_filename) {
	MetaData *metadata = get_metadata();

	unsigned no_of_files = metadata->no_of_files;

	unsigned i;
	for (i = 0; i < no_of_files; i++) {
		if (!strcmp(scan_filename, metadata->files[i].name)) {
			break;
		}
	}
	if (i == no_of_files) {
		printf("File not found\n");
		return;
	}
	int num_of_blocks = metadata->files[i].no_of_blocks;
	int current_block = metadata->files[i].start_block;
	void *buffer = malloc(BLOCK_SIZE);
	int size = metadata->files[i].file_size;
	if (size < BLOCK_SIZE) {
		read_buffer_from_disk(buffer, current_block);
		write_buffer_to_file(buffer, input_file, size);
	}
	else {
		unsigned *block_array = (unsigned *)malloc(BLOCK_SIZE);
		read_buffer_from_disk(block_array, current_block);
		for (int i = 0; i < num_of_blocks - 1; i++) {
			read_buffer_from_disk(buffer, block_array[i]);
			write_buffer_to_file(buffer, input_file, BLOCK_SIZE);
			size -= BLOCK_SIZE;
		}
		read_buffer_from_disk(buffer, block_array[num_of_blocks - 1]);
		write_buffer_to_file(buffer, input_file, size);
	}
}