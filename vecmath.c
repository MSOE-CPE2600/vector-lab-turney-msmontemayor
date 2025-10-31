/**
* Filename: vecmath.h
* Author: Michael S. Montemayor
* Assignment: Lab 5
* Description: declaration of some helper functions for the vector math
*/

#include "vecmath.h"
#include "vec_util.h"
#include <stdio.h>
int perform_math(char* tokens[], int op, int is_stored, vector** vector_mem_ptr){
    switch(op){
        case 1:
        vec_add(tokens, vector_mem_ptr, is_stored);
        break;
        
        case 2:
        vec_sub(tokens, vector_mem_ptr, is_stored);
        break;

        case 3:
        vec_mult(tokens, vector_mem_ptr, is_stored);
        break;

        default:
        printf("not an op");
        return 1;
    }
    return 0;
}

int vec_add(char* tokens[], vector** vector_mem_ptr, int is_stored){
    vector* vector_mem = *vector_mem_ptr;
    int idx1;
    int idx2;
    if(is_stored){
        if((idx1 = vec_index(tokens[2], vector_mem)) == -1){
            return 1; // vector doesnt exist
        }
        if((idx2 = vec_index(tokens[4], vector_mem)) == -1){
            return 1; // vector doesnt exist
        }
        
        int idx_store = vec_index(tokens[0], vector_mem);
        
        double mag1, mag2, mag3;
        mag1 = vector_mem[idx1].mag1 + vector_mem[idx2].mag1;
        mag2 = vector_mem[idx1].mag2 + vector_mem[idx2].mag2;
        mag3 = vector_mem[idx1].mag3 + vector_mem[idx2].mag3;
        
        if (math_vec_create(vector_mem_ptr, idx_store, tokens[0], mag1, mag2, mag3)){
            return 2;
        }
    } else{
        if((idx1 = vec_index(tokens[0], vector_mem)) == -1){
            return 1; // vector doesnt exist
        }
        if((idx2 = vec_index(tokens[2], vector_mem)) == -1){
            return 1; // vector doesnt exist
        }
        
        double mag1, mag2, mag3;
        mag1 = vector_mem[idx1].mag1 + vector_mem[idx2].mag1;
        mag2 = vector_mem[idx1].mag2 + vector_mem[idx2].mag2;
        mag3 = vector_mem[idx1].mag3 + vector_mem[idx2].mag3;
        
        printf("ans = %f %f %f\n", mag1, mag2, mag3);
    }
    return 0;
}

int vec_sub(char* tokens[], vector** vector_mem_ptr, int is_stored) {
    vector* vector_mem = *vector_mem_ptr;
    int idx1, idx2;

    if (is_stored) {
        idx1 = vec_index(tokens[2], vector_mem);
        idx2 = vec_index(tokens[4], vector_mem);
        if (idx1 == -1 || idx2 == -1) return 1;

        int idx_store = vec_index(tokens[0], vector_mem);
        double mag1 = vector_mem[idx1].mag1 - vector_mem[idx2].mag1;
        double mag2 = vector_mem[idx1].mag2 - vector_mem[idx2].mag2;
        double mag3 = vector_mem[idx1].mag3 - vector_mem[idx2].mag3;

        if (math_vec_create(vector_mem_ptr, idx_store, tokens[0], mag1, mag2, mag3))
            return 2;
    } else {
        idx1 = vec_index(tokens[0], vector_mem);
        idx2 = vec_index(tokens[2], vector_mem);
        if (idx1 == -1 || idx2 == -1) return 1;

        double mag1 = vector_mem[idx1].mag1 - vector_mem[idx2].mag1;
        double mag2 = vector_mem[idx1].mag2 - vector_mem[idx2].mag2;
        double mag3 = vector_mem[idx1].mag3 - vector_mem[idx2].mag3;

        printf("ans = %f %f %f\n", mag1, mag2, mag3);
    }
    return 0;
}

int vec_mult(char* tokens[], vector** vector_mem_ptr, int is_stored) {
    vector* vector_mem = *vector_mem_ptr;
    int idx_vec;
    double scalar;

    if (is_stored) {
        int idx_store = vec_index(tokens[0], vector_mem);

        // Try parsing first operand as scalar
        if (get_double(tokens[2], &scalar) == 0) {
            // tokens[2] is scalar, so tokens[4] is vector name
            idx_vec = vec_index(tokens[4], vector_mem);
        } else if (get_double(tokens[4], &scalar) == 0) {
            idx_vec = vec_index(tokens[2], vector_mem);
        } else {
            printf("Invalid operands for scalar multiply\n");
            return 1;
        }

        if (idx_vec == -1) return 1;

        double mag1 = scalar * vector_mem[idx_vec].mag1;
        double mag2 = scalar * vector_mem[idx_vec].mag2;
        double mag3 = scalar * vector_mem[idx_vec].mag3;

        if (math_vec_create(vector_mem_ptr, idx_store, tokens[0], mag1, mag2, mag3))
            return 2;

    } else {
        if (get_double(tokens[0], &scalar) == 0) {
            // first token is scalar
            idx_vec = vec_index(tokens[2], vector_mem);
        } else if (get_double(tokens[2], &scalar) == 0) {
            // last token is scalar
            idx_vec = vec_index(tokens[0], vector_mem);
        } else {
            printf("Invalid operands for scalar multiply\n");
            return 1;
        }

        if (idx_vec == -1) return 1;

        double mag1 = scalar * vector_mem[idx_vec].mag1;
        double mag2 = scalar * vector_mem[idx_vec].mag2;
        double mag3 = scalar * vector_mem[idx_vec].mag3;

        printf("ans = %f %f %f\n", mag1, mag2, mag3);
    }

    return 0;
}