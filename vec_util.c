/**
* Filename: vec_util.h
* Author: Michael S. Montemayor
* Assignment: Lab 5
* Description: definition of some helper functions for the vector memory
*/

#include "vec_util.h"
#include "vecmath.h"
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

int math_vec_create(vector **vector_mem_ptr, int idx, char *name, double mag1, double mag2, double mag3) {
    vector *vector_mem = *vector_mem_ptr;

    if (idx == -1) {
        /* expand array by one slot */
        vector *tmp = realloc(vector_mem, (num_vec_stored + 1) * sizeof(vector));
        if (tmp == NULL) {
            printf("realloc failed");
            return 1;
        }
        vector_mem = tmp;
        *vector_mem_ptr = vector_mem;

        idx = num_vec_stored;
        num_vec_stored++;
    } else {
        if (idx < 0 || idx >= num_vec_stored) {
            fprintf(stderr, "math_vec_create: invalid index %d\n", idx);
            return 1;
        }
    }

    strcpy(vector_mem[idx].name, name);
    vector_mem[idx].mag1 = mag1;
    vector_mem[idx].mag2 = mag2;
    vector_mem[idx].mag3 = mag3;

    printf("%s = %f %f %f\n", vector_mem[idx].name, vector_mem[idx].mag1, vector_mem[idx].mag2, vector_mem[idx].mag3);
    return 0;
}

int vec_create(vector **vector_mem_ptr, char *tokens[], int index) {
    if (!tokens) return 1;
    vector *vector_mem = *vector_mem_ptr;

    if (index == -1) {
        /* expand array by one slot */
        vector *tmp = realloc(vector_mem, (num_vec_stored + 1) * sizeof(vector));
        if (tmp == NULL) {
            printf("realloc failed");
            return 1;
        }
        vector_mem = tmp;
        *vector_mem_ptr = vector_mem;

        index = num_vec_stored;
        num_vec_stored++;
    }

    strcpy(vector_mem[index].name, tokens[0]);

    double mag;
    if (get_double(tokens[2], &mag) != 0) return 1;
    vector_mem[index].mag1 = mag;

    if (get_double(tokens[3], &mag) != 0) return 1;
    vector_mem[index].mag2 = mag;

    if (get_double(tokens[4], &mag) != 0) return 1;
    vector_mem[index].mag3 = mag;

    printf("%s = %f %f %f\n",
           vector_mem[index].name,
           vector_mem[index].mag1,
           vector_mem[index].mag2,
           vector_mem[index].mag3);

    return 0;
}

void clear_vars(vector **vector_mem_ptr) {
    if (*vector_mem_ptr != NULL) {
        free(*vector_mem_ptr);
        *vector_mem_ptr = NULL;
    }
    num_vec_stored = 0;
}

void list_vars(vector vector_mem[]){
    for (int i = 0; i < num_vec_stored; i++){
        printf("%s = %f %f %f\n", vector_mem[i].name, vector_mem[i].mag1, vector_mem[i].mag2, vector_mem[i].mag3);
    }
}

int do_math(char* tokens[], vector **vector_mem_ptr){
    int op;
    if(strcmp(tokens[1], "=") == 0){
        if((op = find_operator(tokens, 1)) == -1){
            return 1;
        }
        perform_math(tokens, op, 1, vector_mem_ptr);
    } else {
        if((op = find_operator(tokens, 0)) == -1){
            return 1;
        }
        perform_math(tokens, op, 0, vector_mem_ptr);
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
int vec_save(const char *filename, vector vector_mem[]) {
    FILE *fp = fopen(filename, "w"); 
    if (!fp) { 
        printf("Error opening file for writing\n"); 
        return 1; 
    } 
    for (int i = 0; i < num_vec_stored; i++) { 
        fprintf(fp, "%s,%lf,%lf,%lf\n", vector_mem[i].name, vector_mem[i].mag1, vector_mem[i].mag2, vector_mem[i].mag3); 
    } 

    fclose(fp); 
    printf("Saved %d vectors to %s\n", num_vec_stored, filename); 
    return 0; 
} 

int vec_load(const char *filename, vector **vector_memory) { 
    FILE *fp = fopen(filename, "r"); 
    if (!fp) { 
        printf("Error opening file\n"); 
        return 1; 
    }
    
    if (*vector_memory != NULL) { 
        free(*vector_memory); 
        *vector_memory = NULL; 
    } 
    
    vector *vector_mem = NULL; 
    num_vec_stored = 0; 
    char line[256]; 
    int line_num = 0; 
    
    while (fgets(line, sizeof(line), fp)) { 
        line_num++; 
        char name[32]; 
        double x, y, z;
        
        if (sscanf(line, "%31[^,],%lf,%lf,%lf", name, &x, &y, &z) != 4) { 
            printf("Malformed lines"); 
            continue;
        }
        
        vector *tmp = realloc(vector_mem, (num_vec_stored + 1) * sizeof(vector)); 
        if (!tmp) { 
            printf("realloc failed"); 
            fclose(fp); 
            free(vector_mem);
            return 1; 
        } 
        vector_mem = tmp;

        strcpy(vector_mem[num_vec_stored].name, name);
        
        vector_mem[num_vec_stored].mag1 = x; 
        vector_mem[num_vec_stored].mag2 = y; 
        vector_mem[num_vec_stored].mag3 = z; 
        num_vec_stored++;
    } 
    
    fclose(fp); 
    *vector_memory = vector_mem; 
    printf("Loaded %d vectors from %s\n", num_vec_stored, filename); 
    return 0; 
}
