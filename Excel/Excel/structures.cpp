#include "structures.h"
#include <stdlib.h>

Cell *createCell(char *data, Type type) {
	Cell *newCell = (Cell *)malloc(sizeof(Cell));
	newCell->data = data;
	newCell->mode = type;
	return newCell;
}

Header *createHeader(char *head, Type type) {
	Header *header = (Header *)malloc(sizeof(Header));
	header->head = head;
	header->mode = type;
	return header;
}