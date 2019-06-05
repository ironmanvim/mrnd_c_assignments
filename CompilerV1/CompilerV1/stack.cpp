#include "stack.h"

void push(int *stack, int *top, int data) {
	stack[++(*top)] = data;
}

int pop(int *stack, int *top) {
	return stack[(*top)--];
}
