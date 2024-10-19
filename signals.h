/*---------- ID HEADER -------------------------------------
/  Author(s):   Andrew Boisvert, Kyle Scidmore
/  Email(s):    abois526@mtroyal.ca, kscid125@mtroyal.ca
/  File Name:   signals.h
/
/  Program Purpose(s):
/    User-defined header file for signals.c. 
/---------------------------------------------------------*/

#ifndef SIGNAL_H
#define SIGNAL_H
#define MAX_BG_JOBS 10 

// Structure to hold information about background jobs
typedef struct {
    pid_t pid;           // Process ID of the background job
    char pid_str[32];    // String representation of the PID
    int job_num;
} BackgroundJob;


extern BackgroundJob bg_jobs[MAX_BG_JOBS];
extern int num_bg_jobs; 
extern volatile sig_atomic_t child_exit; 


void child_signal(int sig);
void interrupt_block(int sig);
void reap_children();

#endif