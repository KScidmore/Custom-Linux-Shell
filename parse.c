/*---------- ID HEADER -------------------------------------
/  Author(s):   Andrew Boisvert, Kyle Scidmore
/  Email(s):    abois526@mtroyal.ca, kscid125@mtroyal.ca
/  File Name:   parse.c
/
/  Program Purpose(s):
/    TODO
/---------------------------------------------------------*/

#include <sys/types.h>
#include "jobs.h"
#include "parse.h"
#include "commands.h"
#include "globals.h"
#include "stringlib.h"
#include "search.h"
#include "memory.h"

/* delete later, for debugging */
#include <stdio.h>
#include <string.h>

/*---------- FUNCTION: parse_command -----------------------
/  PURPOSE:
/    TODO - purpose from the caller's perspective 
/  
/  CALLER INPUT:
/    Command *command
/      TODO 
/    char *tokens[]
/      TODO 
/    Job *job
/      TODO 
/  
/  CALLER OUTPUT:
/    N/A--No return value.
/  
/  ASSUMPTIONS, LIMITATIONS, AND KNOWN BUGS:
/    TODO - N/A or list them 
/---------------------------------------------------------*/
void parse_command(Command *command, char *tokens[], Job *job){

    int i = 0;
    command->argc = 0;

    while(tokens[i] != NULL){

        if(string_comp(tokens[i], "<") == 0){
            job->infile_path = tokens[i + 1];
            i += 2;

        }else if(string_comp(tokens[i], ">") == 0){

            job->outfile_path = tokens[i + 1];
            i += 2;

            
        }else if(string_comp(tokens[i], "&") == 0){
           
            job->background = 1;
            i++;
            
        }else{

            command->argv[command->argc++] = tokens[i];
            i++;
        }
    }

    command->argv[command->argc] = NULL;

}

/*---------- FUNCTION: parse_pipeline ----------------------
/  PURPOSE:
/    TODO - purpose from the caller's perspective 
/  
/  CALLER INPUT:
/    Job *job
/      TODO 
/    char *tokens[]
/      TODO 
/  
/  CALLER OUTPUT:
/    N/A--No return value.
/  
/  ASSUMPTIONS, LIMITATIONS, AND KNOWN BUGS:
/    TODO - N/A or list them 
/---------------------------------------------------------*/
void parse_pipeline(Job *job, char *tokens[]){

    int stage = 0;
    int start = 0;
    int i;

    for(i = 0; tokens[i] != NULL; i++){

        if(string_comp(tokens[i], "|") == 0){
            
            tokens[i] = NULL; /*Splits stages*/
            parse_command(&job->pipeline[stage], &tokens[start], job);
            stage++;
            start = i + 1;

        }
    }
    
    if(tokens[start] != NULL){

        parse_command(&job->pipeline[stage], &tokens[start], job);
        stage++;
    }

    job->num_stages = stage;

}

/*---------- FUNCTION: parse_job ---------------------------
/  PURPOSE:
/    TODO - purpose from the caller's perspective 
/  
/  CALLER INPUT:
/    Job *job
/      TODO 

/  
/  CALLER OUTPUT:
/    N/A--No return value.
/  
/  ASSUMPTIONS, LIMITATIONS, AND KNOWN BUGS:
/    TODO - N/A or list them 
/---------------------------------------------------------*/
void parse_job(Job *job, char *envp[]){
    int i = 0;
    char path[MAX_PATH_LEN];
    char *tokens[MAX_ARGS];
    char *full_tokens[MAX_ARGS];


    get_command(tokens);

    for (i = 0; tokens[i] != NULL; i++) {
        if (tokens[i][0] != '-' &&
            tokens[i][0] != '|' &&
            tokens[i][0] != '<' &&
            tokens[i][0] != '>') {
            
            if (check_for_file(tokens[i], path, envp) == 0) { 
                /*
                string_copy(path, full_tokens[i]);
                */
                if (tokens[0] != NULL) {
                    printf("tokens[0] is *NOT* NULL\n\r");
                    strncpy(tokens[i], path, MAX_PATH_LEN - 1);
                } else {
                    printf("tokens[0] is NULL\n\r");
                }
            } 
        } else {
            
        }
    }

    if (tokens[0] == NULL || tokens[0][0] == '\0'){
        return;
    }

    parse_pipeline(job, tokens);
    
}