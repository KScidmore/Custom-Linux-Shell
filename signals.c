/*---------- ID HEADER -------------------------------------
/  Author(s):   Andrew Boisvert, Kyle Scidmore
/  Email(s):    abois526@mtroyal.ca, kscid125@mtroyal.ca
/  File Name:   signals.c
/
/  Program Purpose(s):
/    This module handles signal management for child processes
/    and interrupts.
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
/    Handles the SIGCHLD signal. This function reaps child 
/    processes that have exited to prevent zombie processes.
/  
/  CALLER INPUT:
/    int sig
/      The signal number received.
/  
/  CALLER OUTPUT:
/    N/A--No return value.
/  
/  ASSUMPTIONS, LIMITATIONS, AND KNOWN BUGS:
/    - Does not provide feedback on the status of terminated 
/      child processes, which may limit debugging capabilities.
/      (Having prompt issues with output may add later)
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
/    Handles the SIGINT signal. Preventing Ctrl-C from
/    terminating the shell during user input.
/  
/  CALLER INPUT:
/    int sig
/      The signal number received.
/  
/  CALLER OUTPUT:
/    N/A-No return value.
/  
/  ASSUMPTIONS, LIMITATIONS, AND KNOWN BUGS:
/   N/A
/---------------------------------------------------------*/
void interrupt_block(int sig){

    /*do nothing*/

}