/**
* Filename: mem_util.h
* Author: Michael S. Montemayor
* Assignment: Lab 5
* Description: declaration of some helper functions for the vector memory
*/

#ifndef MEM_UTIL_H
#define MEM_UTIL_H

#include "vecmath.h"

int vec_index(char* name, vector vector_mem[]);
int vec_create(vector vector_mem[], char* tokens[], int index);
int do_math(char* tokens[], vector vector_mem[]);
void clear_vars(void);
void list_vars(vector vector_mem[]);
int find_operator(char* tokens[], int is_stored);
int get_double(const char* str, double *result);
int math_vec_create(vector vector_mem[], int idx, char* name, double mag1, double mag2, double mag3);

#endif
