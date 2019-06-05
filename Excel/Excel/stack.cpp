#include "stack.h"

void push(char **stack, int *top, char *value) {
	stack[++(*top)] = value;
}

char *pop(char **stack, int *top) {
	return stack[(*top)--];
}