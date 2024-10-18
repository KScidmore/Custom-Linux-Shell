/*---------- ID HEADER -------------------------------------
/  Author(s):   Andrew Boisvert, Kyle Scidmore
/  Email(s):    abois526@mtroyal.ca, kscid125@mtroyal.ca
/  File Name:   commands.c 
/
/  Program Purpose(s):
/    TODO
/---------------------------------------------------------*/

#include <stdio.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>
#include "errorcodes.h"
#include "commands.h"
#include "memory.h"
#include "prompt.h"
#include "signals.h"

/*---------- FUNCTION: get_command -------------------------
/  PURPOSE:
/    TODO - purpose from the caller's perspective 
/  
/  CALLER INPUT:
/    char *tokens[]
/      TODO
/  
/  CALLER OUTPUT:
/    N/A--No return value.
/  
/  ASSUMPTIONS, LIMITATIONS, AND KNOWN BUGS:
/    TODO - N/A or list them 
/---------------------------------------------------------*/
void get_command(char *tokens[]) {

    ssize_t bytes_read;
    char *p_buffer;
    

    p_buffer = alloc(BUFFER_SIZE);
    if (p_buffer == NULL) {
        write(1, ERROR_MEMORY, sizeof(ERROR_MEMORY) - 1);
        return;
    }

    bytes_read = read(0, p_buffer, BUFFER_SIZE - 1);

    if (bytes_read > 0) {
        p_buffer[bytes_read] = '\0'; /* same as *(p_buffer + bytes_read) */

        if (p_buffer[0] == '\n' || p_buffer[0] == '\0') {
            free_all();
            return;
        }

    }
    else {
        write(2, ERROR_READ, sizeof(ERROR_READ) - 1);
        return;
    }
    
    tokenize(tokens, p_buffer);

    free_all();

}

/*---------- FUNCTION: run_command -------------------------
/  PURPOSE:
/    TODO - purpose from the caller's perspective 
/  
/  CALLER INPUT:
/    Command *command
/      TODO
/  
/  CALLER OUTPUT:
/    N/A--No return value.
/  
/  ASSUMPTIONS, LIMITATIONS, AND KNOWN BUGS:
/    TODO - N/A or list them 
/---------------------------------------------------------*/
void run_command(Command *command) {

    pid_t pid;
    int status;
    char * const newenvp[] = {NULL};
    pid = fork();

    if (pid == 0) {
        if (execve(command->argv[0] , command->argv , newenvp) == -1) {
            write(2, ERROR_INVALID_COMMAND, sizeof(ERROR_INVALID_COMMAND) - 1);
            _exit(1); /* make sure child exits if error */
        }
    }
    else {
        waitpid(pid, &status, 0);
    }

}


/*---------- FUNCTION: tokenize ----------------------------
/  PURPOSE:
/    This function breaks a buffer of user input into seperate 
/    command line arguments (tokens), using whitespace as the 
/    delimiter value. 
/  
/  CALLER INPUT:
/    char *tokens[]
/      TODO
/    char buffer[]
/      TODO
/  
/  CALLER OUTPUT:
/    N/A--No return value.
/  
/  ASSUMPTIONS, LIMITATIONS, AND KNOWN BUGS:
/    TODO - N/A or list them 
/---------------------------------------------------------*/
void tokenize(char *tokens[], char buffer[]) {

    int i = 0;
    int token_index = 0; /*tracks the index of next token to be placed in array*/
    char *start = 0; /*pointer for start of string being tokenized*/

    while (buffer[i] != '\0') { /*runs till end of buffer*/

        if (buffer[i] != ' ' && buffer[i] != '\n') { /*checks for whitespace or carriage return*/

            if (start == 0) { /*if start is null */

                start = &buffer[i]; /*set start to point at the start of token to be copied*/
            }
        }
        else { /*else whitespace is found*/

            if (start != 0) { /*if start already points to a token to be copied*/

                buffer[i] = '\0'; /*null terminate token*/
                tokens[token_index++] = start; /*set tokens at specified index to point at start of token*/
                start = 0; /* ANSI_RESET start*/
            }
        }

        i++;

    }

    if (start != 0) { /*check to make sure all tokens were accounted for*/

        tokens[token_index++] = start; 

    }

    tokens[token_index] = 0; /*null terminate token array*/

}
