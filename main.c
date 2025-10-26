/**
* filename: main.c
* author: Michael S. Montemayor
* assignment: Lab 5
* Description: Vector caluculator
*/

#include "prompt.h"
#include <signal.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

int main(int argc, char* argv[]){
    if (argc > 1) {
        if (strcmp(argv[1], "-h") == 0 || strcmp(argv[1], "--help") == 0) {
            print_help();
            return 0;
        } else {
            printf("Unknown option: %s\n", argv[1]);
            printf("Use '-h' or '--help' for usage information.\n");
            return 1;
        }
    }
    
    atexit(cleanup);
    signal(SIGINT, handle_sigint);

    while(1){
        display_prompt();
    }
}
