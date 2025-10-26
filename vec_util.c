/**
* Filename: vec_util.h
* Author: Michael S. Montemayor
* Assignment: Lab 5
* Description: definition of some helper functions for the vector memory
*/

#include "vec_util.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//store the number of vectors stored
int num_vec_stored = 0;

int vec_index(char* name, vector vector_mem[]){
    for(int i = 0; i<num_vec_stored; i++){
        if(strcmp(name, vector_mem[i].name) == 0){
            return i;
        }
    }
    return -1;
}

int math_vec_create(vector vector_mem[], int idx, char* name, double mag1, double mag2, double mag3){
    if(idx == -1){
        if(num_vec_stored == 9){
            return 2;
        }
        idx = num_vec_stored;
        num_vec_stored++;
    }

    strcpy(vector_mem[idx].name, name);
    vector_mem[idx].mag1 = mag1;
    vector_mem[idx].mag2 = mag2;
    vector_mem[idx].mag3 = mag3;

    printf("%s = %f %f %f\n", vector_mem[idx].name, vector_mem[idx].mag1, vector_mem[idx].mag2, vector_mem[idx].mag3);
    return 0;
}

int vec_create(vector vector_mem[], char* tokens[], int index){

    if(vector_mem == NULL){
        vector_mem = malloc(10 * sizeof(vector));
        if (vector_mem == NULL) {
            printf("initial malloc failed");
        }
    }

    if(index == -1){
        if(num_vec_stored == 10){ //10 - initial size
            num_vec_stored ++;

            vector *tmp = realloc(vector_mem, num_vec_stored * sizeof(vector));

            if (tmp == NULL) {
                printf("realloc failed");
                return 1;
            }

            vector_mem = tmp;
        }
        index = num_vec_stored;
    }

    strcpy(vector_mem[index].name, tokens[0]);
    double mag;
    if(get_double(tokens[2], &mag) != 1){
        vector_mem[index].mag1 = mag;
    } else {
        return 1;
    }
    if(get_double(tokens[3], &mag) != 1){
        vector_mem[index].mag2 = mag;
    } else {
        return 1;
    }   
    if(get_double(tokens[4], &mag) != 1){
        vector_mem[index].mag3 = mag;
    } else {
        return 1;
    }

    printf("%s = %f %f %f\n", vector_mem[index].name, vector_mem[index].mag1, vector_mem[index].mag2, vector_mem[index].mag3);
    return 0;
}

void clear_vars(vector vector_mem[]){
    num_vec_stored = 0;
    free(vector_mem);
}

void list_vars(vector vector_mem[]){
    for (int i = 0; i < num_vec_stored; i++){
        printf("%s = %f %f %f\n", vector_mem[i].name, vector_mem[i].mag1, vector_mem[i].mag2, vector_mem[i].mag3);
    }
}

int do_math(char* tokens[], vector vector_mem[]){
    int op;
    if(strcmp(tokens[1], "=") == 0){
        if((op = find_operator(tokens, 1)) == -1){
            return 1;
        }
        perform_math(tokens, op, 1, vector_mem);
    } else {
        if((op = find_operator(tokens, 0)) == -1){
            return 1;
        }
        perform_math(tokens, op, 0, vector_mem);
    }
    return 0;
}

int find_operator(char* tokens[], int is_stored){
    int idx;

    if(is_stored){
        idx = 3;
    } else {
        idx = 1;
    }
    if(strcmp(tokens[idx], "+") == 0){
        return 1;
    } else if(strcmp(tokens[idx], "-") == 0){
        return 2;
    } else if(strcmp(tokens[idx], "*") == 0){
        return 3;
    }

    return -1;
}

int get_double(const char* str, double* result) {
    char* endptr;

    *result = strtod(str, &endptr);

    if(endptr == str){
        return 1; //invalid magnitude
    }

    return 0;
}


