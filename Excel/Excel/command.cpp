#include "command.h"
#include "tokenizer.h"
#include "structures.h"
#include "expression.h"
#include "analyzer.h"
#include "stack.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int evaluateInfixExpression(char *expression, Cell ***sheet);
int isNotBraces(char *string) {
	if (!strcmp(string, "(") || !strcmp(string, ")")) {
		return 0;
	}
	return 1;
}
int checkIsANumber(char *string) {
	int i;
	for (i = 0; string[i] != '\0'; i++) {
		if (!isdigit(string[i]))
			return 0;
	}
	return 1;
}
int isCoordinate(char *string) {
	if (isalpha(string[0]) && isdigit(string[1]))
		return 1;
	return 0;
}
int *getCoordinate(char *coordinateString) {
	int *XY = (int *)malloc(sizeof(int) * 2);
	XY[1] = coordinateString[0] - 'A';
	XY[0] = coordinateString[1] - '0' - 1;
	return XY;
}
Cell *getCell(char *coordinate, Cell ***sheet) {
	if (isCoordinate(coordinate)) {
		int *XY = getCoordinate(coordinate);
		return sheet[XY[0]][XY[1]];
	}
	return NULL;
}
int validateExpression(char *expression) {
	return 0;
}
int checkNoErrors(char *cell, char *expression, Cell ***sheet) {
	int tokens_len = 0;
	char **tokens = tokenize(expression, &tokens_len);
	for (int i = 0; i < tokens_len; i++) {
		if (!isOperator(tokens[i]) && !checkIsANumber(tokens[i]) && isNotBraces(tokens[i])) {
			if (strcmp(cell, tokens[i])) {
				Cell *current = getCell(tokens[i], sheet);
				if (current->mode == EXPRESSION) {
					if (checkNoErrors(cell, current->data, sheet)) {

					}
					else {
						return 0;
					}
				}
				else if (current->mode == STRING) {
					return 0;
				}
			}
			else {
				return 0;
			}
		}
	}
	return 1;
}
int evaluatePostfixExpression(char *expression, Cell ***sheet) {
	char *stack[100];
	int top = -1;
	int tokensLen = 0;
	char **tokens = tokenize(expression, &tokensLen);
	for (int i = 0; i < tokensLen; i++) {
		if (isOperator(tokens[i])) {
			char *op = tokens[i];
			char *firstString = pop(stack, &top);
			char *secondString = pop(stack, &top);
			int val1, val2;
			if (isCoordinate(secondString)) {
				Cell *second = getCell(secondString, sheet);
				if (second->mode == INTEGER) {
					val1 = _atoi64(second->data);
				}
				else {
					val1 = evaluateInfixExpression(second->data, sheet);
				}
			}
			else {
				val1 = _atoi64(secondString);
			}
			if (isCoordinate(firstString)) {
				Cell *first = getCell(firstString, sheet);
				if (first->mode == INTEGER) {
					val2 = _atoi64(first->data);
				}
				else {
					val2 = evaluateInfixExpression(first->data, sheet);
				}
			}
			else {
				val2 = _atoi64(firstString);
			}
			int res = doOperation(val1, op, val2);
			char *number = (char *)malloc(sizeof(char) * 100);
			_itoa(res, number, 10);
			push(stack, &top, number);
		}
		else {
			push(stack, &top, tokens[i]);
		}
	}
	return _atoi64(pop(stack, &top));
}
int evaluateInfixExpression(char *expression, Cell ***sheet) {
	int is_possible = 1;
	char *newExpression = (char *)malloc(sizeof(int) * 100);
	newExpression[0] = '\0';
	strcat(newExpression, "(");
	strcat(newExpression, expression);
	strcat(newExpression, ")");
	char *postfix = convertToPostfix(newExpression, &is_possible);
	return evaluatePostfixExpression(postfix, sheet);
}
void clearTokens(char ***tokens, int tokens_count) {
	for (int i = 0; i < tokens_count; i++) {
		free((*tokens)[i]);
	}
	free(*tokens);
}
void commandExecuter(char **command, int command_len, Cell ***sheet, char *save, Header **header) {
	if (command_len == 0) {
		return;
	}
	if (!strcmp(command[0], "GET")) {
		if (command_len == 2 && strlen(command[1]) == 2 && isCoordinate(command[1])) {
			Cell *cell = getCell(command[1], sheet);
			if (cell->mode == EXPRESSION) {
				printf("%d (%s)\n", evaluateInfixExpression(cell->data, sheet), cell->data);
			}
			else {
				printf("%s\n", cell->data);
			}
		}
		else {
			printf("ARGUMENTS PARSING FAILED\n");
		}
	}
	else if (!strcmp(command[0], "SET")) {
		if (command_len > 2) {
			Cell *cell = getCell(command[1], sheet);
			if (cell != NULL) {
				if (!strcmp(command[2], "=") && command_len >= 4) {
					if (checkIsANumber(command[3]) && command_len == 4) {
						char *string = (char *)malloc(sizeof(char) * 100);
						cell->mode = INTEGER;
						strcpy(string, command[3]);
						cell->data = string;
					}
					else if (!strcmp(command[3], "\"")) {
						char *string = (char *)malloc(sizeof(char) * 100);
						string[0] = '\0';
						for (int i = 4; strcmp(command[i], "\"") && i < command_len; i++) {
							strcat(string, command[i]);
							strcat(string, " ");
						}
						cell->mode = STRING;
						cell->data = string;
					}
					else {
						char *formula = deTokenize(command+3, command_len-3);
						int is_possible = 1;
						char *newExpression = (char *)malloc(sizeof(int) * 100);
						newExpression[0] = '\0';
						strcat(newExpression, "(");
						strcat(newExpression, formula);
						strcat(newExpression, ")");
						convertToPostfix(newExpression, &is_possible);
						if (is_possible) {
							if (checkNoErrors(command[1], formula, sheet)) {
								cell->mode = EXPRESSION;
								cell->data = formula;
							}
						}
						else {
							cell->mode = STRING;
							cell->data = formula;
						}
					}
				}
				else {
					printf("ARGUMENTS PARSING FAILED\n");
				}
			}
			else {
				printf("ARGUMENTS PARSING FAILED\n");
			}
		}
		else {
			printf("ARGUMENTS PARSING FAILED\n");
		}
	}
	else if (!strcmp(command[0], "PRINT")) {
		printf("\t");
		for (char ch = 'A'; ch - 'A' < 10; ch++) {
			printf("%c\t", ch);
		}
		printf("\n");
		printf("\t");
		for (char ch = 'A'; ch - 'A' < 10; ch++) {
			printf("_\t", ch);
		}
		printf("\n");
		for (int i = 0; i < 10; i++) {
			printf("%d|\t", i + 1);
			for (int j = 0; j < 10; j++) {
				if (sheet[i][j]->mode == EXPRESSION) {
					printf("%d\t", evaluateInfixExpression(sheet[i][j]->data, sheet));
				}
				else {
					printf("%s\t", sheet[i][j]->data);
				}
			}
			printf("\n");
		}
	}
	else if (!strcmp(command[0], "IMPORT")) {
		if (command_len >= 2) {
			char file[50] = "";
			if (command_len == 4) {
				strcat(file, command[1]);
				strcat(file, command[2]);
				strcat(file, command[3]);
			}
			else if (command_len >= 2) {
				strcat(file, command[1]);
				strcat(file, ".csv");
			}
			else {
				printf("ARGUMENTS PARSING FAILED\n");
			}
			FILE *fptr = fopen(file, "r");
			if (command_len == 5) {
				if (!strcmp(command[2], "HEADER")) {
					if (!strcmp(command[3], "=")) {
						if (!strcmp(command[4], "TRUE")) {
							char *value = (char *)malloc(sizeof(char) * 100);
							for (int i = 0; i < 10; i++) {
								fscanf(fptr, "%[^,\n]%[,\n]", value);
								int tokenLen = 0;
								char **tokens = tokenize(value, &tokenLen);
								header[i]->head = tokens[0];
								header[i]->mode = INTEGER;
								if (tokenLen == 3) {
									if (!strcmp(tokens[2], "INT"))
										header[i]->mode = INTEGER;
									else if (!strcmp(tokens[2], "STRING"))
										header[i]->mode = STRING;
								}
							}
						}
						else if (!strcmp(command[4], "FALSE")) {

						}
						else {
							printf("ARGUMENT PARSING FAILED\n");
						}
					}
					else {
						printf("ARGUMENT PARSING FAILED\n");
					}
				}
				else {
					printf("ARGUMENT PARSING FAILED\n");
				}
			}
			for (int i = 0; i < 10; i++) {
				for (int j = 0; j < 10; j++) {
					char *value = (char *)malloc(sizeof(char) * 100);
					fscanf(fptr, "%[^,\n]%[,\n]%[\n]", value);
					if (checkIsANumber(value)) {
						sheet[i][j]->data = value;
						sheet[i][j]->mode = INTEGER;
					}
					else {
						int stringsLen = 0;
						char **strings = tokenize(value, &stringsLen);
						if (strcmp(strings[0], "\"")) {
							int is_possible = 1;
							convertToPostfix(value, &is_possible);
							if (is_possible) {
								sheet[i][j]->data = value;
								sheet[i][j]->mode = EXPRESSION;
							}
							else {
								sheet[i][j]->data = value;
								sheet[i][j]->mode = STRING;
							}
						}
						else {
							char *string = (char *)malloc(sizeof(char) * 100);
							for (int i = 1; strcmp(command[i], "\"") && i < command_len; i++) {
								strcat(string, command[i]);
								strcat(string, " ");
							}
							sheet[i][j]->mode = STRING;
							sheet[i][j]->data = string;
						}
					}
				}
			}
			fclose(fptr);
			strcpy(save, file);
		}
	}
	else if (!strcmp(command[0], "EXPORT")) {
		char file[50] = "";
		if (command_len == 4) {
			strcat(file, command[1]);
			strcat(file, command[2]);
			strcat(file, command[3]);
		}
		else if(command_len == 2) {
			strcat(file, command[1]);
			strcat(file, ".csv");
		} 
		else {
			printf("ARGUMENTS PARSING FAILED\n");
			return;
		}
		FILE *fptr = fopen(file, "w");
		for (int i = 0; i < 10; i++) {
			for (int j = 0; j < 10; j++) {
				if (sheet[i][j]->mode == STRING) {
					fprintf(fptr, "\"%s,\"", sheet[i][j]->data);
				}
				else {
					fprintf(fptr, "%d,", sheet[i][j]->data);
				}
			}
			fprintf(fptr, "\n");
		}
		fclose(fptr);
		strcpy(save, file);
	}
	else if (!strcmp(command[0], "SAVE")) {
		if (!strcmp("", save)) {
			printf("No file to save\n");
		}
		else {
			FILE *fptr = fopen(save, "w");
			for (int i = 0; i < 10; i++) {
				for (int j = 0; j < 10; j++) {
					if (sheet[i][j]->mode == STRING) {
						fprintf(fptr, "\"%s,\"", sheet[i][j]->data);
					}
					else {
						fprintf(fptr, "%d,", sheet[i][j]->data);
					}
				}
				fprintf(fptr, "\n");
			}
			fclose(fptr);
		}
	}
	else if (!strcmp(command[0], "EXIT")) {
		exit(0);
	}
	else {
		printf("INVALID COMMAND\n");
	}
	//clearTokens(&command, command_len);
}