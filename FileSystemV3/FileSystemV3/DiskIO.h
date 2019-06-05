#ifndef _BLOCK_IO_H
#define _BLOCK_IO_H

unsigned init(char *hard_disk_name, unsigned block_size);
int read_block(void *buffer, unsigned block_number);
int write_block(void *buffer, unsigned block_number);
int close();

#endif