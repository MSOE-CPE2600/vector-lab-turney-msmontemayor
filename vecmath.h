/**
* Filename: vecmath.h
* Author: Michael S. Montemayor
* Assignment: Lab 5
* Description: declaration of some helper functions for the vector math
*/

#ifndef VECMATH_H
#define VECMATH_H

#include "vector.h"

int perform_math(char* tokens[], int op, int is_stored, vector **vector_mem);
int vec_add(char* tokens[], vector **vector_mem, int is_stored);
int vec_sub(char* tokens[], vector **vector_mem, int is_stored);
int vec_mult(char* tokens[], vector **vector_mem, int is_stored);

#endif

