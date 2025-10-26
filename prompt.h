/**
* Filename: prompt.h
* Author: Michael S. Montemayor
* Assignment: Lab 5
* Description: declares the functions to create the prompt and determine user input
*/

#ifndef PROMPT_H
#define PROMPT_H

int display_prompt(void);
int tokenize_input(char* user_input);
int single_token(char* token);
int three_toks(char* tokens[]);
int four_toks(char* tokens[]);
int five_toks(char* tokens[]);
void print_help(void);
void cleanup(void);
void handle_sigint(int sig);

#endif
