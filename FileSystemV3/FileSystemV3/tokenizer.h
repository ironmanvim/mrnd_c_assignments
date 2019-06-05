#ifndef _TOKENIZER_H
#define _TOKENIZER_H

char **tokenize(char *commandString, int *command_length);
char *deTokenize(char **tokens, int tokensLen);

#endif