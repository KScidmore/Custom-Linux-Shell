/*---------- ID HEADER -------------------------------------
/  Author(s):   Andrew Boisvert, Kyle Scidmore
/  Email(s):    abois526@mtroyal.ca, kscid125@mtroyal.ca
/  File Name:   echo.c
/
/  Program Purpose(s):
/    TODO
/---------------------------------------------------------*/

/* INCLUDES (<> then "") */
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include "stringlib.h"

/* DEFINES */
#define BUFFER_SIZE 1024
#define MAX_TOKENS 256
#define HEAP_SIZE 1024
#define MAX_ARGS 12 /* can change this as we see fit */

/* DATA TYPES (STRUCTS, ETC) */
/*---------- STRUCTURE: Command ----------------------------
/  INFO:
/    Data structure for representing Linux commands.
/  
/  ATTRIBUTES:
/    char *argv - an array of pointers to dyn-alloc'ed strings
/    unsigned int argc - argument count (the size of the array)
/---------------------------------------------------------*/
typedef struct {
    char *argv[MAX_ARGS+1];
    unsigned int argc;
    /* it is noted that we may need to add more here, later */
} Command;


/* GLOBALS */
char heap[HEAP_SIZE];
char *p_heap = heap;

void tokenize(char *tokens[], char buffer[]);

int main(){

    struct Command command;

    get_command(&command);

    while(1){

        run_command(&command);
        get_command(&command);
        
    }


    return 0;
}