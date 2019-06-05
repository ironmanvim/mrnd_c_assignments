#ifndef _TABLES_H
#define _TABLES_H

struct Label {
	char block_name[20];
	unsigned address;
};

struct Symbol {
	char symbol[20];
	unsigned address;
	unsigned size;
};

#endif