/*---------- ID HEADER -------------------------------------
/  Author(s):   Andrew Boisvert, Kyle Scidmore
/  Email(s):    abois526@mtroyal.ca, kscid125@mtroyal.ca
/  File Name:   signals.c
/
/  Program Purpose(s):
/    TODO
/---------------------------------------------------------*/
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>
#include <errno.h>
#include <sys/wait.h>
#include "signals.h"
#include "globals.h"
#include "prompt.h"


/*---------- FUNCTION: child_signal ------------------------
/  PURPOSE:
/    TODO - purpose from the caller's perspective 
/  
/  CALLER INPUT:
/    TODO - purpose of input parameters 
/  
/  CALLER OUTPUT:
/    TODO
/  
/  ASSUMPTIONS, LIMITATIONS, AND KNOWN BUGS:
/    TODO - N/A or list them 
/---------------------------------------------------------*/
void child_signal(int sig){

    int old_errno = errno;
    pid_t pid;
    int status;
    int exit_status;

    while((pid = waitpid(-1, &status, WNOHANG)) > 0){


    }
    errno = old_errno;
}

/*---------- FUNCTION: interrupt_block ---------------------
/  PURPOSE:
/    TODO - purpose from the caller's perspective 
/  
/  CALLER INPUT:
/    TODO - purpose of input parameters 
/  
/  CALLER OUTPUT:
/    TODO
/  
/  ASSUMPTIONS, LIMITATIONS, AND KNOWN BUGS:
/    TODO - N/A or list them 
/---------------------------------------------------------*/
void interrupt_block(int sig){

    /*do nothing*/

}