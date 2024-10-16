/*---------- ID HEADER -------------------------------------
/  Author(s):   Andrew Boisvert, Kyle Scidmore
/  Email(s):    abois526@mtroyal.ca, kscid125@mtroyal.ca
/  File Name:   jobs.h
/
/  Program Purpose(s):
/    TODO
/---------------------------------------------------------*/

#ifndef JOBS_H
#define JOBS_H

#include <stddef.h>
#include "commands.h"

#define MAX_PIPELINE_LENGTH 2

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

void init_job(Job *job);
void get_job(Job *job);
void run_job(Job *job);

#endif