#ifndef _STRUCTURES_H
#define _STRUCTURES_H

enum Type {
	INTEGER, EXPRESSION, STRING
};
typedef enum Type Type;

struct Cell {
	//int data;
	char *data;
	//char *formula;
	Type mode;
};
typedef struct Cell Cell;

Cell *createCell(char *data, Type type);

struct Header {
	char *head;
	Type mode;
};
typedef struct Header Header;

Header *createHeader(char *head, Type type);

#endif