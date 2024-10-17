/*---------- ID HEADER -------------------------------------
/  Author(s):   Andrew Boisvert, Kyle Scidmore
/  Email(s):    abois526@mtroyal.ca, kscid125@mtroyal.ca
/  File Name:   stringlib.h
/
/  Program Purpose(s):
/    TODO
/---------------------------------------------------------*/

#include <stdio.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>
#include "errorcodes.h"
#include "commands.h"
#include "memory.h"
#include "prompt.h"

/*---------- FUNCTION: TODO --------------------------------
/  PURPOSE:
/    TODO - purpose from the caller's perspective 
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
void get_command(Command *command) {

    ssize_t bytes_read;
    char *p_buffer;

    show_prompt();

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


    tokenize(command->argv, p_buffer);
    free_all();
}

/*---------- FUNCTION: TODO --------------------------------
/  PURPOSE:
/    TODO - purpose from the caller's perspective 
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


/*---------- FUNCTION: TODO --------------------------------
/  PURPOSE:
/    TODO - purpose from the caller's perspective 
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
/*breaks buffer into command line arguments (tokens) based on whitespace*/
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

/usr/bin/ls -al | /usr/bin/ls -al > /usr/bin/ls -al
tokens[/usr/bin/ls, -al , | , /usr/bin/ls, -al , > , /usr/bin/ls, al]


/usr/bin/ls -al /library | /usr/bin/wc -l > dirlistlen &

ls -al /library | wc -l >> filename.txt &


textfile:
"ls contents
"

ls > lscontents.txt

wc < lscontents.txt 

9

void wrapper(){

}

#define ERRCHK_WRITE(fd, buf, len) 