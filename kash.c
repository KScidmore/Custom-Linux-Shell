/*---------- id header -------------------------------------
/  author(s):   andrew boisvert, kyle scidmore
/  email(s):    abois526@mtroyal.ca, kscid125@mtroyal.ca
/  file name:   kash.c
/
/  program purpose(s):
/    todo
/---------------------------------------------------------*/

/* includes (<> then "") */
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "stringlib.h"

/* defines */
#define HEAP_SIZE 4096 /* 4kb of memory */
#define MAX_ARGS 256 
#define BUFFER_SIZE 1024
#define MAX_PIPELINE_LENGTH 2

/* data types (structs, etc) */
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

/*---------- structure: command ----------------------------
/  info:
/    data structure for representing a job.
/  
/  attributes:
/    Command pipeline[MAX_PIPELINE_LENGTH];
/      TODO
/    unsigned int num_stages;
/      TODO - also expand upon below 
/    char *outfile_path;   
/      NULL for no output redirection
/    char *infile_path;    
/      NULL for no input redirection
/    int background;       
/      0 = foreground, !0 = background
/---------------------------------------------------------*/
typedef struct {
    Command pipeline[MAX_PIPELINE_LENGTH];
    unsigned int num_stages;
    char *outfile_path;
    char *infile_path;
    int background;
} Job;

/* globals */
char heap[HEAP_SIZE];
char *p_free_heap = heap;

/* function prototypes */
int string_comp(const char *str1, const char *str2);
void tokenize(char *tokens[], char buffer[]);
char *alloc(unsigned int size);
void free_all();
void get_command(Command *command);
void run_command(Command *command);
void get_job(Command *command);
void run_job(Command *command);
void init_job(Job *job);
char *mystrtok(char *tokens[], char buffer[], const char *delimiters);

int main() {

    Command command;
    Job job;

    get_job(&command);

    if (string_comp(command.argv[0], "exit") == 1) {
        return 0;
    }

    while (1) {
        run_job(&command);
        get_job(&command);

        if(string_comp(command.argv[0], "exit") == 1){
            break;
        }
    }

    return 0;
}


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
                start = 0; /* reset start*/
            }
        }

        i++;

    }

    if (start != 0) { /*check to make sure all tokens were accounted for*/

        tokens[token_index++] = start; 

    }

    tokens[token_index] = 0; /*null terminate token array*/

}

char *alloc(unsigned int size) {
    /*Calculate the new pointer after allocation*/
    char *new_free_heap = p_free_heap + size;
    
    /*Check if the new pointer would exceed the allocated heap size*/
    if (new_free_heap <= (p_free_heap + HEAP_SIZE)) {
        char *p_alloced = p_free_heap;
        p_free_heap = new_free_heap;
        return p_alloced;
    } else {
        return NULL; /* error if memory runs out, but shouldn't reach this */
    }
}

void free_all() {
    p_free_heap = heap;
}

void get_command(Command *command) {

    const char *p_dollar = "$ ";
    ssize_t bytes_read;
    char *p_buffer;

    write(2, p_dollar, 2);

    p_buffer = alloc(buffer_size);
    if (p_buffer == NULL) {
        write(1, "memory allocation failure!\n", 27);
        return;
    }

    bytes_read = read(0, p_buffer, buffer_size - 1);
    if (bytes_read > 0) {
        p_buffer[bytes_read] = '\0'; /* same as *(p_buffer + bytes_read) */
    }
    else {

        write(2, "failed to read input!\n", 22);
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

    if (pid == 0) {
        execve(command->argv[0] , command->argv , newenvp);
    }

    waitpid(pid, &status, 0);
}

int string_comp(const char * str1,const char * str2){

    while (*str1 && *str2) {

        if (*str1 != *str2) {
            return -1;
        }
        str1++;
        str2++;
    }

    if (*str1 != *str2) {
        return -1;
    }

    return 1;
}

void get_job(Command *command, Job *job) {

    const char *p_dollar = "$ ";
    ssize_t bytes_read;
    char *p_buffer;

    write(2, p_dollar, 2);

    p_buffer = alloc(BUFFER_SIZE);
    if (p_buffer == NULL) {
        write(1, "Error: memory allocation failure.\n", 27);
        return;
    }

    bytes_read = read(0, p_buffer, BUFFER_SIZE - 1);

    if (bytes_read > 0) {
        p_buffer[bytes_read] = '\0'; /* same as *(p_buffer + bytes_read) */
    }
    else {
        write(2, "Error: failed to read input.\n", 22);
        return;
    }

    free_all();

    tokenize(command->argv, p_buffer);
}

void run_job(Command *command, Job *job) {

    pid_t pid;
    int status;
    char * const newenvp[] = {NULL};

    pid = fork();
    if (pid == -1) {
        perror("Error: fork failed.");
    }

    if (pid == 0) {
        execve(command->argv[0] , command->argv , newenvp);
    }

    waitpid(pid, &status, 0);
}

void init_job(Job *job) {
    job->num_stages = 0;
    job->outfile_path = NULL;
    job->infile_path = NULL;
    job->background = 0;
}

void mystrtok(char *string, const char *delimiter) {
    int i = 0;
    int token_index = 0; 
    char *start = 0; 

    while (buffer[i] != '\0') { /*runs till end of buffer*/
        if (!is_delimiter(buffer[i], delimiters)) {
            if (buffer[i] != ' ' && buffer[i] != '\n') { 
                if (start == 0) { /*if start is null */
                    start = &buffer[i]; /*set start to point at the start of token to be copied*/
                }
            }
        }
        else { /*else whitespace is found*/
            if (start != 0) { /*if start already points to a token to be copied*/
                buffer[i] = '\0'; /*null terminate token*/
                tokens[token_index++] = start; /*set tokens at specified index to point at start of token*/
                start = 0; /* reset start*/
            }
        }
        i++;
    }

    if (start != 0) { /*check to make sure all tokens were accounted for*/
        tokens[token_index++] = start; 
    }

    tokens[token_index] = 0; /*null terminate token array*/
}

/* helper function for mystrtok */
int is_delimiter(char ch, const char delimiters[]) {
    for (int i = 0; delimiters[i] != \0; i++) {
        if (ch == delimiters[i]) {
            return 1;
        }
    }
    return 0;
}