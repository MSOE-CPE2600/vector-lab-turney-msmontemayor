/**
* Filename: prompt.c
* Author: Michael S. Montemayor
* Assignment: Lab 5
* Description: defines the functions to create the prompt and determine user input
*/

#include "prompt.h"
#include "vec_util.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define INPUT_LEN 80

char user_input[INPUT_LEN];
char* tokens[INPUT_LEN/2];

vector vector_mem[10];

int display_prompt(void){
    printf("minimat>");
    fgets(user_input, 80, stdin);
    
    return tokenize_input(user_input);
}


int tokenize_input(char* user_input){
    user_input[strcspn(user_input, "\n")] = '\0';
    tokens[0] = strtok(user_input, " ");


    //check for only one token
    if((tokens[1] = strtok(NULL, " ")) == NULL){
        if(single_token(tokens[0])){
            return 1;
        }
    } else if((tokens[2] = strtok(NULL, " ")) == NULL){
        return 1;
    } else if((tokens[3] = strtok(NULL, " ")) == NULL){ // 3 inputs
        three_toks(tokens);
    } else if((tokens[4] = strtok(NULL, " ")) == NULL){ // 4 inputs
        four_toks(tokens);
    } else if((tokens[5] = strtok(NULL, " ")) == NULL){ // 5 inputs
        five_toks(tokens);
    } else {
        printf("invalid input\n"); // 1, 2 or more than 5 inputs
    }
    return 0;
}

int single_token(char* token){
    char* single_cmds[] = {"quit", "clear", "list"};

    int index;
    if(strcmp(token, single_cmds[0]) == 0){
        exit(0);
    } else if(strcmp(token, single_cmds[1]) == 0){
        clear_vars();
    } else if(strcmp(token, single_cmds[2]) == 0){
        list_vars(vector_mem);
    } else if((index = vec_index(tokens[0], vector_mem)) != -1){
        printf("%s = %f %f %f\n", vector_mem[index].name, vector_mem[index].mag1, vector_mem[index].mag2, vector_mem[index].mag3);
    } else {
        //return 1 on error
        printf("Invalid Input\n");
        return 1;
    }

    //return 0 on success
    return 0;
}

int three_toks(char* tokens[]){
    int index;
    if(strcmp(tokens[1], "=") == 0){
        index = vec_index(tokens[0], vector_mem);
        //assign vector
        tokens[3] = "0.0";
        tokens[4] = "0.0";
        if(vec_create(vector_mem, tokens, index)){
            return 1;
        }
        printf("3 tok assign\n");
        return 0;
    } else{
        //check for valid operator and perform 
        do_math(tokens, vector_mem);
    }
    return 0;
}

int four_toks(char* tokens[]){
    int index;
    if(strcmp(tokens[1], "=") == 0){
        index = vec_index(tokens[0], vector_mem);
        tokens[4] = "0.0";
        if(vec_create(vector_mem, tokens, index)){
            return 1;
        }
    } else {
        printf("invalid input four toks 2");
        return 1;
    }

    return 0;
}

int five_toks(char* tokens[]) {
    int index;
    int op = find_operator(tokens, 1); 

    if (strcmp(tokens[1], "=") != 0) {
        return 1; // all 5 token inputs should have assignments
    }

    index = vec_index(tokens[0], vector_mem);

    if (op == -1) {
        if (vec_create(vector_mem, tokens, index)) {
            return 1;
        }
        return 0;
    }

    // Has operator: do math operation and assign result
    return do_math(tokens, vector_mem);
}

void print_help(void) {
    printf("Vector Math Calculator\n");
    printf("Usage:\n");
    printf("  minimat               Start interactive prompt\n");
    printf("  minimat -h            Show this help message\n\n");

    printf("Commands:\n");
    printf("  list                  List all stored vectors\n");
    printf("  clear                 Clear all stored vectors\n");
    printf("  quit                  Exit the program\n\n");

    printf("Vector Operations:\n");
    printf("  A = 1.0 2.0 3.0       Create or overwrite vector A\n");
    printf("  A                     Display vector A\n");
    printf("  A = B + C             Add vectors\n");
    printf("  A = B - C             Subtract vectors\n");
    printf("  A = 2 * B             Scalar multiply\n");
    printf("  A = B * 2             Scalar multiply\n\n");

    printf("Other Notes:\n");
    printf("  Up to 10 vectors may be stored.\n");
    printf("  Invalid inputs will print an error message.\n");
}
