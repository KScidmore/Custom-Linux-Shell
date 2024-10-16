/*---------- ID HEADER -------------------------------------
/  Author(s):   Andrew Boisvert, Kyle Scidmore
/  Email(s):    abois526@mtroyal.ca, kscid125@mtroyal.ca
/  File Name:   jobs.c
/
/  Program Purpose(s):
/    TODO
/---------------------------------------------------------*/

#include "jobs.h"

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
void init_job(Job *job) {
    job->num_stages = 0;
    job->outfile_path = NULL;
    job->infile_path = NULL;
    job->background = 0;
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
void get_job(Job *job) {
    Command *command = &job->pipeline[0];

    get_command(command);

    job->num_stages = 1;
    job->background = 0;

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
void run_job(Job *job) {
    Command *command = &job->pipeline[0];
    run_command(command);
}