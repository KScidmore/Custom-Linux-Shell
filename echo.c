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

/* FUNCTION PROTOTYPES */
int stringComp(const char *str1, const char *str2);
void tokenize(char *tokens[], char buffer[]);

/* CODE, STARTING WITH MAIN */
int main(){

    Command command; 

    const char *dollar = "$ ";
    char buffer[BUFFER_SIZE];
    char *tokens[MAX_TOKENS];
    ssize_t bytesRead;

    int i, j;

    write(1, dollar, 2);

    while(1){

        bytesRead = read(0, buffer, 1024 - 1);

        buffer[bytesRead] = '\0';
        if (stringComp(buffer, "exit\n") == 1){
            break;
        }
        write(1, buffer, bytesRead);

        tokenize(tokens, buffer);

        for(i = 0; tokens[i] != 0; i++){
            j = 0;
            while(tokens[i][j] != '\0'){
                write(1, &tokens[i][j], 1);
                j++;
            }

            write(1, "\n" , 1);
        }
        write(1, dollar, 2);
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


/*---------- FUNCTION: *alloc ------------------------------
/  PURPOSE:
/    Returns a pointer to a chunk of the given size. 
/  
/  CALLER INPUT:
/    size - the given size to be assigned 
/  
/  CALLER OUTPUT:
/    TODO - purpose of output parameters and return vals
/  
/  ASSUMPTIONS, LIMITATIONS, AND KNOWN BUGS:
/    TODO - N/A or list them 
/
/  CITATIONS:
/    TODO - N/A or list them
/---------------------------------------------------------*/
char *alloc(unsigned int size) {
    if (p_heap + size <= HEAP_SIZE) {
        char *temp = p_heap;
        p_heap += size;
        return temp;
    }
    else {
        return NULL; /* error if memory runs out, but shouldn't reach this*/
    }
}

/*---------- FUNCTION: free_all ----------------------------
/  PURPOSE:
/    Returns all previously allocated memory to the heap.
/  
/  CALLER INPUT:
/    N/A
/  
/  CALLER OUTPUT:
/    N/A
/  
/  ASSUMPTIONS, LIMITATIONS, AND KNOWN BUGS:
/    N/A
/
/  CITATIONS:
/    N/A
/---------------------------------------------------------*/
void free_all() {
    p_heap = heap;
}

/*---------- FUNCTION: get_command -------------------------
/  PURPOSE:
/    Prompts the user to enter a command line, then reads a
/    command line into a buffer, handling cases such as command
/    lines that are too long. The function then calls free_all()
/    to reset the heap, tokenizes the command line, and populates 
/    the command structure's attributes. 
/  
/  CALLER INPUT:
/    TODO - purpose of input parameters 
/  
/  CALLER OUTPUT:
/    TODO - purpose of output parameters and return vals
/  
/  ASSUMPTIONS, LIMITATIONS, AND KNOWN BUGS:
/    TODO - N/A or list them 
/
/  CITATIONS:
/    TODO - N/A or list them
/---------------------------------------------------------*/
void get_command() {
    const char *dollar = "$ ";
    char heap[BUFFER_SIZE];
    ssize_t bytesRead;
    write(1, dollar, 2);

    bytesRead = read(0, heap, HEAP_SIZE - 1);
    heap[bytesRead] = '\0';

    free_all();

    tokenize(command->argv, heap);

    /* might need to edit, want you to check it out */


}

/*---------- FUNCTION: run_command -------------------------
/  PURPOSE:
/    Processes the given command by attempting to spawn a
/    corresponding child process, making use of the fork,
/    execve, and waitpid system calls. 
/  
/  CALLER INPUT:
/    TODO - purpose of input parameters 
/  
/  CALLER OUTPUT:
/    TODO - purpose of output parameters and return vals
/  
/  ASSUMPTIONS, LIMITATIONS, AND KNOWN BUGS:
/    TODO - N/A or list them 
/
/  CITATIONS:
/    TODO - N/A or list them
/---------------------------------------------------------*/
void run_command() {
    /* TODO */
}