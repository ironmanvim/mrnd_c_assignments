#include "tokenizer.h"
#include "analyzer.h"
#include "expression.h"
#include <ctype.h>
#include <stdio.h>
#include <string.h>

int isID(char *string) {
	if (isalpha(string[0]) && isdigit(string[1]))
		return 1;
	return 0;
}
int expressionSyntaxAnalyzer(char *expression) {
	int tokensLen = 0;
	char **tokens = tokenize(expression, &tokensLen);
	int breaker = 0, i;

	int state = 0;
	for (i = 0; i < tokensLen && !breaker; i++) {
		switch(state) {
		case 0:
			if (isID(tokens[i])) {
				state = 1;
			}
			else if (isID(tokens[i])) {

			}
			else {
				state = -1;
				breaker = 1;
			}
			break;
		case 1:
			if (isOperator(tokens[i])) {
				state = 0;
			}
			else {
				state = -1;
				breaker = 1;
			}
			break;
		}
	}
	i--;
	if (i != tokensLen && state != 1) {
		printf("Syntax Error: (Expression) After (=) at %d (%s)\n", i+1, tokens[i]);
		return 0;
	}
	return 1;
}
