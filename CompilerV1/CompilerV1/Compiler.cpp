#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "tokenizer.h"
#include "stack.h"

struct OpCode {
	unsigned opcode;
	int no_of_parameters = 0;
	unsigned parameters[5];
};

struct Label {
	char block_name[20];
	unsigned address;
};

struct Symbol {
	char symbol[20];
	unsigned address;
	unsigned size;
};

enum opcode {
	MOV=1, MOV2, ADD, SUB, MUL,JMP, IF, EQ, LT, GT, LTEQ, GTEQ, PRINT, READ
};

enum registers {
	AX, BX, CX, DX, EX, FX, GX, HX
};


int isSymbol(char *string) {
	if (!strcmp(string, "DATA") || !strcmp(string, "CONST")) {
		return 1;
	}
	return 0;
}
int isData(char *string) {
	if (!strcmp(string, "DATA")) {
		return 1;
	}
	return 0;
}
int isConst(char *string) {
	if (!strcmp(string, "CONST")) {
		return 1;
	}
	return 0;
}
int isOperation(char *string) {
	if (!strcmp(string, "READ") 
		|| !strcmp(string, "MOV")
		|| !strcmp(string, "ADD")
		|| !strcmp(string, "SUB")
		|| !strcmp(string, "MUL")
		|| !strcmp(string, "PRINT")
		|| !strcmp(string, "READ")) {
		return 1;
	}
	return 0;
}
int isRegister(char *string) {
	if (isalpha(string[0]) && isalpha(string[1]) && string[1] == 'X') {
		return 1;
	}
	return 0;
}
int getOpCode(char *code) {
	char op[14][10] = {
		"MOV", "MOV2", "ADD", "SUB", "MUL", "JMP", "IF", "EQ", "LT", "GT", "LTEQ", "GTEQ", "PRINT", "READ",
	};
	for (int i = 0; i < 14; i++) {
		if (!strcmp(op[i], code))
			return i + 1;
	}
	return -1;
}
int get_register(char *code) {
	char op[14][3] = {
		"AX", "BX", "CX", "DX", "EX", "FX", "GX", "HX",
	};
	for (int i = 0; i < 8; i++) {
		if (!strcmp(op[i], code))
			return i;
	}
	return -1;
}

char **read_input(FILE *input_file, int *no_of_lines) {
	*no_of_lines = 0;
	char **lines = (char **)malloc(sizeof(char *) * 100);
	for (int i = 0; i < 100; i++) {
		lines[i] = (char *)malloc(sizeof(char) * 100);
	}

	char *input = (char *)malloc(sizeof(char) * 100);
	while (fscanf(input_file, "%[^\n]\n", input) != EOF) {
		lines[(*no_of_lines)][0] = '\0';
		strcpy(lines[(*no_of_lines)++], input);
	}
	free(input);
	
	return lines;
}
void push_to_symbol_table(Symbol **symbol_table, int *no_of_entries, Symbol *symbol) {
	symbol_table[(*no_of_entries)++] = symbol;
}
void push_to_opcode_table(OpCode **opcode_table, int *no_of_entries, OpCode *opcode) {
	opcode_table[(*no_of_entries)++] = opcode;
}
void push_to_label_table(Label **label_table, int *no_of_entries, Label *label) {
	label_table[(*no_of_entries)++] = label;
}
void process_symbol(Symbol **symbol_table, 
	int *no_of_entries, 
	char **tokens, int no_of_tokens, unsigned *store_address) {

	Symbol *symbol = (Symbol *)malloc(sizeof(Symbol));
	strcpy(symbol->symbol, tokens[1]);
	if (isConst(tokens[0])) {
		symbol->address = (*store_address)++;
		symbol->size = 0;
	}
	else if (no_of_tokens == 2) {
		symbol->address = (*store_address)++;
		symbol->size = 1;
	}
	else if (no_of_tokens == 5) {
		unsigned no_of_bytes = atoi(tokens[3]);
		symbol->address = (*store_address);
		(*store_address) += no_of_bytes;
		symbol->size = no_of_bytes;
	}
	push_to_symbol_table(symbol_table, no_of_entries, symbol);
}
Symbol *get_symbol(Symbol **symbol_table, int no_of_symbols, char *symbol) {
	for (int i = 0; i < no_of_symbols; i++) {
		if (!strcmp(symbol_table[i]->symbol, symbol))
			return symbol_table[i];
	}
	return NULL;
}
Label *get_label(Label **label_table, int no_of_lables, char *label) {
	for (int i = 0; i < no_of_lables; i++) {
		if (!strcmp(label_table[i]->block_name, label)) {
			return label_table[i];
		}
	}
	return NULL;
}
void process_label(Label **label_table, 
	int *no_of_entries, 
	char **token, int no_of_tokens, unsigned instruction_address) {

	Label *label = (Label *)malloc(sizeof(Label));
	strcpy(label->block_name, token[0]);
	label->address = instruction_address+1;
	push_to_label_table(label_table, no_of_entries, label);
}
void process_if(OpCode **opcode_table, int *no_of_opcode, int *stack, int *top, char **tokens, int no_of_tokens) {
	push(stack, top, (*no_of_opcode));
	OpCode *opcode = (OpCode *)malloc(sizeof(OpCode));
	opcode->opcode = IF;
	opcode->parameters[0] = get_register(tokens[1]);
	opcode->parameters[1] = get_register(tokens[3]);
	opcode->parameters[2] = getOpCode(tokens[2]);
	opcode->parameters[3] = 0;
	opcode->no_of_parameters = 4;
	push_to_opcode_table(opcode_table, no_of_opcode, opcode);
}
void process_else(OpCode **opcode_table, int *no_of_opcode, int *stack, int *top, char **tokens, int no_of_tokens) {
	push(stack, top, *no_of_opcode);
	OpCode *opcode = (OpCode *)malloc(sizeof(OpCode));
	opcode->opcode = JMP;
	opcode->parameters[0] = 0;
	opcode->parameters[1] = 0;
	opcode->parameters[2] = 0;
	opcode->parameters[3] = 0;
	opcode->no_of_parameters = 1;
	push_to_opcode_table(opcode_table, no_of_opcode, opcode);
}
void process_endif(OpCode **opcode_table, int *no_of_opcode, int *stack, int *top) {
	int goto_instruction = pop(stack, top);
	int parameter = *no_of_opcode;
	while (opcode_table[goto_instruction]->opcode != IF) {
		opcode_table[goto_instruction]->parameters[0] = parameter + 1;
		parameter = goto_instruction + 1;
		goto_instruction = pop(stack, top);
	}
	opcode_table[goto_instruction]->parameters[3] = parameter + 1;
}
void process_operation(OpCode **opcode_table, int *no_of_opcode, 
	char **tokens, int no_of_tokens, Symbol **symbol_table, int no_of_symbols) {
	OpCode *opcode = (OpCode *)malloc(sizeof(OpCode));
	opcode->opcode = getOpCode(tokens[0]);
	if (!strcmp(tokens[0], "READ")) {
		opcode->parameters[0] = get_register(tokens[1]);
		opcode->parameters[1] = 0;
		opcode->parameters[2] = 0;
		opcode->parameters[3] = 0;
		opcode->no_of_parameters = 1;
	}
	else if (!strcmp(tokens[0], "MOV")) {
		if (isRegister(tokens[1]) && no_of_tokens == 4) {
			opcode->opcode = MOV2;
			opcode->parameters[0] = get_register(tokens[1]);
			opcode->parameters[1] =  get_symbol(symbol_table, no_of_symbols, tokens[3])->address;
		}
		else if (no_of_tokens == 4) {
			opcode->parameters[0] = get_symbol(symbol_table, no_of_symbols, tokens[1])->address;
			opcode->parameters[1] = get_register(tokens[3]);
		}
		else if (isRegister(tokens[1]) && no_of_tokens == 7) {
			opcode->opcode = MOV2;
			opcode->parameters[0] = get_register(tokens[1]); 
			opcode->parameters[1] = get_symbol(symbol_table, no_of_symbols, tokens[3])->address + atoi(tokens[5]);
		}
		else {
			
			opcode->parameters[0] = get_symbol(symbol_table, no_of_symbols, tokens[1])->address + atoi(tokens[3]);
			opcode->parameters[1] = get_register(tokens[6]);
		}
		opcode->parameters[2] = 0;
		opcode->parameters[3] = 0;
		opcode->no_of_parameters = 2;
	}
	else if (!strcmp(tokens[0], "ADD") || !strcmp(tokens[0], "SUB") || !strcmp(tokens[0], "MUL")) {
		opcode->parameters[0] = get_register(tokens[1]);
		opcode->parameters[1] = get_register(tokens[3]);
		opcode->parameters[2] = get_register(tokens[5]);
		opcode->parameters[3] = 0;
		opcode->no_of_parameters = 3;
	}
	else if (!strcmp(tokens[0], "PRINT")) {
		opcode->parameters[0] = get_symbol(symbol_table, no_of_symbols, tokens[1])->address;
		opcode->parameters[1] = 0;
		opcode->parameters[2] = 0;
		opcode->parameters[3] = 0;
		opcode->no_of_parameters = 1;
	}
	push_to_opcode_table(opcode_table, no_of_opcode, opcode);
}
void process_jump(Label **label_table, int no_of_labels, char **tokens, int tokens_len, OpCode **opcode_table, int *no_of_opcode) {
	OpCode *opcode = (OpCode *)malloc(sizeof(OpCode));
	opcode->opcode = getOpCode(tokens[0]);
	opcode->parameters[0] = get_label(label_table, no_of_labels, tokens[1])->address;
	opcode->parameters[1] = 0;
	opcode->parameters[2] = 0;
	opcode->parameters[3] = 0;
	opcode->no_of_parameters = 1;
	push_to_opcode_table(opcode_table, no_of_opcode, opcode);
}
void process_tokens(char **tokens, 
	int no_of_tokens, Symbol **symbol_table, 
	int *no_of_symbols, Label **label_table, int *no_of_labels, OpCode **opcode_table, 
	int *no_of_opcode, unsigned *store_address, int *stack, int *top) {
	
	if (isSymbol(tokens[0])) {
		process_symbol(symbol_table, no_of_symbols, tokens, no_of_tokens, store_address);
	}
	else if (isOperation(tokens[0])) {
		process_operation(opcode_table, no_of_opcode, tokens, no_of_tokens, symbol_table, *no_of_symbols);
	}
	else if (no_of_tokens == 2 && !strcmp(tokens[1], ":")) {
		process_label(label_table, no_of_labels, tokens, no_of_tokens, (*no_of_opcode));
	}
	else if (!strcmp(tokens[0], "IF")) {
		process_if(opcode_table, no_of_opcode, stack, top, tokens, no_of_tokens);
	}
	else if (!strcmp(tokens[0], "ELSE")) {
		process_else(opcode_table, no_of_opcode, stack, top, tokens, no_of_tokens);
	}
	else if(!strcmp(tokens[0], "ENDIF")) {
		process_endif(opcode_table, no_of_opcode, stack, top);
	}
	else if (!strcmp(tokens[0], "JMP")) {
		process_jump(label_table, *no_of_labels, tokens, no_of_tokens, opcode_table, no_of_opcode);
	}

}
void process_opcode_of_file(char *filename, char *output_filename) {
	int no_oF_symbols = 0;
	int no_of_labels = 0;
	int no_of_opcode = 0;
	int top = -1;
	Symbol **symbol_table = (Symbol **)malloc(sizeof(Symbol *));
	Label **label_table = (Label **)malloc(sizeof(Label *));
	OpCode **opcode_table = (OpCode **)malloc(sizeof(OpCode *));
	int stack[100];
	unsigned store_address = 0;


	FILE *input_file = fopen(filename, "r");
	FILE *output_file = fopen(output_filename, "w");
	int no_of_lines = 0;
	char **lines = read_input(input_file, &no_of_lines);
	for (int i = 0; i < no_of_lines; i++) {
		int no_of_tokens = 0;
		char **tokens = tokenize(lines[i], &no_of_tokens);
		process_tokens(tokens, no_of_tokens, 
			symbol_table, &no_oF_symbols, 
			label_table, &no_of_labels, 
			opcode_table, &no_of_opcode, &store_address
			,stack, &top);
	}
	printf("symbol table: \n");
	for (int i = 0; i < no_oF_symbols; i++) {
		printf("%s  %d  %d\n", symbol_table[i]->symbol, symbol_table[i]->address, symbol_table[i]->size);
		
	}
	printf("Opcode table: \n");
	for (int i = 0; i < no_of_opcode; i++) {
		fprintf(output_file, "%d %d ", i + 1, opcode_table[i]->opcode);
		for (int j = 0; j < opcode_table[i]->no_of_parameters; j++) {
			fprintf(output_file, "%d ", opcode_table[i]->parameters[j]);
		}
		fprintf(output_file, "\n");
	}
	fclose(input_file);
	fclose(output_file);
	getchar();
}