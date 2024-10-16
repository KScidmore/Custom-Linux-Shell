/*---------- ID HEADER -------------------------------------
/  Author(s):   Andrew Boisvert, Kyle Scidmore
/  Email(s):    abois526@mtroyal.ca, kscid125@mtroyal.ca
/  File Name:   stringlib.h
/
/  Program Purpose(s):
/    TODO
/---------------------------------------------------------*/

#ifndef COMMANDS_H
#define COMMANDS_H

#define MAX_ARGS 256 
#define BUFFER_SIZE 1024

/*---------- structure: command ----------------------------
/  info:
/    data structure for representing linux commands.
/  
/  attributes:
/    char *argv - an array of pointers to dyn-alloc'ed strings
/    unsigned int argc - argument count (the size of the array)
/---------------------------------------------------------*/
typedef struct {
    char *argv[MAX_ARGS+1];
    unsigned int argc;
    /* it is noted that we may need to add more here, later */
} Command;

void get_command(Command *command);
void run_command(Command *command);
void tokenize(char *tokens[], char buffer[]);

#endif