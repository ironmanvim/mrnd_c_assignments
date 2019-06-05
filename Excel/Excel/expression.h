#ifndef _EXPRESSION_H
#define _EXPRESSION_H

char *convertToPostfix(char *expression, int *is_possible);
int getOperatorPriority(char *op);
int isOperator(char *op);
int doOperation(int a, char *op, int b);

#endif