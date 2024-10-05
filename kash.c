/*---------- ID HEADER -------------------------------------
/  Author(s):   Andrew Boisvert, Kyle Scidmore
/  Email(s):    abois526@mtroyal.ca, kscid125@mtroyal.ca
/  File Name:   kash.c
/
/  Program Purpose(s):
/    TODO
/---------------------------------------------------------*/

/* INCLUDES (<> then "") */
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "stringlib.h"

/* DEFINES */
#define HEAP_SIZE 4096 /* 4KB of memory */
#define MAX_ARGS 256 
#define BUFFER_SIZE 1024
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
char *p_free_heap = heap;

/* FUNCTION PROTOTYPES */
int stringComp(const char *str1, const char *str2);
void tokenize(char *tokens[], char buffer[]);
char *alloc(unsigned int size);
void free_all();
void get_command(Command *command);
void run_command(Command *command);

int main(){

    Command command;

    get_command(&command);

    while(1){

        run_command(&command);
        get_command(&command);
        
    }


    return 0;
}


/*Breaks buffer into command line arguments (tokens) based on whitespace*/
void tokenize(char *tokens[], char buffer[]){

    int i = 0;
    int tokenIndex = 0; /*tracks the index of next token to be placed in array*/
    char *start = 0; /*Pointer For start of string being tokenized*/

    while(buffer[i] != '\0'){ /*Runs till end of buffer*/

        if(buffer[i] != ' ' && buffer[i] != '\n'){ /*checks for whitespace or carriage return*/

            if(start == 0){ /*if start is Null */

                start = &buffer[i]; /*Set start to point at the start of token to be copied*/
            }
        }
        else{ /*Else whitespace IS found*/

            if(start != 0){ /*If start already points to a token to be copied*/

                buffer[i] = '\0'; /*Null terminate token*/
                tokens[tokenIndex++] = start; /*set tokens at specified index to point at start of token*/
                start = 0; /* reset start*/
            }
        }

        i++;

    }

    if(start != 0){ /*Check to make sure all tokens were accounted for*/

        tokens[tokenIndex++] = start; 

    }

    tokens[tokenIndex] = 0; /*Null terminate token array*/

}

char *alloc(unsigned int size) {
    if (p_free_heap + size <= HEAP_SIZE) {
        char *p_alloced = p_free_heap;
        p_free_heap += size;
        return p_alloced;
    }
    else {
        return NULL; /* error if memory runs out, but shouldn't reach this*/
    }
}

void free_all() {
    p_free_heap = heap;
}

void get_command(struct Command *command) {

    const char *p_dollar = "$ ";
    ssize_t bytes_read;
    char *p_buffer;

    write(2, p_dollar, 2);

    p_buffer = alloc(BUFFER_SIZE);
    if (p_buffer == NULL) {
        write(1, "Memory allocation failure!\n", 27);
        return;
    }

    bytes_read = read(0, p_buffer, BUFFER_SIZE - 1);
    if(bytes_read > 0){
        p_buffer[bytes_read] = '\0'; /* same as *(p_buffer + bytes_read) */
    }
    else {

        write(2, "Failed to read input!\n");
        return;
    }

    free_all();

    tokenize(command->argv, p_buffer);


}

void run_command(Command *command) {

    pid_t pid;
    int status;
    char * const newenvp[] = {NULL};
    pid = fork();

    if(pid == 0){

        execve(command->argv[0] , command->argv , newenvp);
        
    }

    waitpid(pid, &status, 0);

}

    

int stringComp(const char * str1,const char * str2){

    while(*str1 && *str2){

        if(*str1 != *str2){

            return -1;
        }
        str1++;
        str2++;
    }
    if(*str1 != *str2){

        return -1;
    }

    return 1;
    
}