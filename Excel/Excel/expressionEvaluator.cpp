#include <stdio.h>
#include "expression.h"
#include "tokenizer.h"
#include <string.h>
#include "stack.h"
#include <stdlib.h>


int doOperation(int a, char *op, int b) {
	if (!strcmp(op, "+")) {
		return a + b;
	}
	else if (!strcmp(op, "-")) {
		return a - b;
	}
	else if (!strcmp(op, "*")) {
		return a * b;
	}
	else if (!strcmp(op, "/")) {
		return a / b;
	}
}
int getOperatorPriority(char *op) {
	if (!strcmp(op, "(")) {
		return 5;
	}
	else if (!strcmp(op, "^")) {
		return 4;
	}
	else if (!strcmp(op, "%")) {
		return 3;
	}
	else if (!strcmp(op, "*") || !strcmp(op, "/")) {
		return 2;
	}
	else if (!strcmp(op, "+") || !strcmp(op, "-")) {
		return 1;
	}
	return 0;
}
int isOperator(char *op) {
	if (!strcmp(op, "(") || !strcmp(op, "^") || !strcmp(op, "%") || !strcmp(op, "*") || !strcmp(op, "/") || !strcmp(op, "+") || !strcmp(op, "-")) {
		return 1;
	}
	return 0;
}
char *convertToPostfix(char *expression, int *is_possible) {
	int expressionTokensLen;
	char **expressionTokens = tokenize(expression, &expressionTokensLen);
	char *res = (char *)malloc(sizeof(char) * 1000);
	res[0] = '\0';
	int k = 0;
	char *stack[100];
	int top = -1;
	push(stack, &top, "$");
	for (int i = 0; i < expressionTokensLen; i++) {
		if (!strcmp(expressionTokens[i], ")")) {
			while (strcmp(stack[top], "(")) {
				char *temp = pop(stack, &top);
				strcat(res, temp);
				strcat(res, " ");
			}
			pop(stack, &top);
		}
		else if (!isOperator(expressionTokens[i])) {
			strcat(res, expressionTokens[i]);
			strcat(res, " ");
		}
		else {
			if (getOperatorPriority(expressionTokens[i]) > getOperatorPriority(stack[top])) {
				push(stack, &top, expressionTokens[i]);
			}
			else {
				while (getOperatorPriority(stack[top]) >= getOperatorPriority(expressionTokens[i]) && strcmp(stack[top], "(") && strcmp(stack[top], "$")) {
					char *temp = pop(stack, &top);
					strcat(res, temp);
					strcat(res, " ");
				}
				push(stack, &top, expressionTokens[i]);
			}
		}
	}
	/*while (strcmp(stack[top], "$")) {
		char *temp = pop(stack, &top);
		strcat(res, temp);
		strcat(res, " ");
	}*/
	if (!strcmp(stack[top], "$")) {
		*is_possible = 1;
	}
	else {
		*is_possible = 0;
	}
	return res;
}

int evaluateExpression(char *expression) {
	int is_possible = 0;
	char *postfixExpression = convertToPostfix(expression, &is_possible);
	return 0;
}
