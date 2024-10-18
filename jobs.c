/*---------- ID HEADER -------------------------------------
/  Author(s):   Andrew Boisvert, Kyle Scidmore
/  Email(s):    abois526@mtroyal.ca, kscid125@mtroyal.ca
/  File Name:   jobs.c
/
/  Program Purpose(s):
/    TODO
/---------------------------------------------------------*/

#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include "jobs.h"
#include "globals.h"
#include "errorcodes.h"
#include "stringlib.h"
#include "signals.h"

#define READ_END  0
#define WRITE_END 1


/*---------- FUNCTION: init_job ----------------------------
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
void init_job(Job *job) {
    job->num_stages = 0;
    job->outfile_path = NULL;
    job->infile_path = NULL;
    job->background = 0;
}


/*---------- FUNCTION: run_job -----------------------------
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
void run_job(Job *job){

    int stage;
    int status;
    pid_t pids[job->num_stages];
    char pid_str[32];
    int pipefd[2 * (job->num_stages - 1)];

    for (stage = 0; stage < job->num_stages - 1; stage++){
        if (pipe(pipefd + stage * 2) == -1) {

            write(STDERR, ERROR_PIPE_FAILED, string_len(ERROR_PIPE_FAILED));
            exit(1);

        }
    }

    for(stage = 0; stage < job->num_stages; stage++){

        pids[stage] = process_job(job, stage, pipefd);

    }

    for (stage = 0; stage < job->num_stages - 1; stage++) {
        close(pipefd[stage * 2]);     
        close(pipefd[stage * 2 + 1]); 
    }

    if(!job->background){

        for(stage = 0; stage < job->num_stages; stage++){
            waitpid(pids[stage], &status, 0);
    
        }

    }else{
        write(STDOUT, "Background job PID: ", 21);

        pid_to_string(pids[0], pid_str);
        pid_str[string_len(pid_str)] = '\n';

        write(STDOUT, pid_str, string_len(pid_str));
    }
    
    signal(SIGINT, interrupt_block); 
}

/*---------- FUNCTION: process_job -------------------------
/  PURPOSE:
/    TODO - purpose from the caller's perspective 
/  
/  CALLER INPUT:
/    Job *job
/      TODO 
/    int stage
/      TODO 
/    int *pipefd
/      TODO 
/    
/  CALLER OUTPUT:
/    TODO - purpose of output parameters and return vals
/  
/  ASSUMPTIONS, LIMITATIONS, AND KNOWN BUGS:
/    TODO - N/A or list them 
/---------------------------------------------------------*/
pid_t process_job(Job *job, int stage, int *pipefd){


    pid_t pid;

    int input_fd = -1;
    int output_fd = -1;
    int i;

    pid = fork();

    if(pid == 0){ /*Child starts here*/

        signal(SIGINT, SIG_DFL);

        /*Process input redirection*/
        if (stage == 0 && job->infile_path != NULL){
            input_fd = open(job->infile_path, O_RDONLY);

            if(input_fd < 0){
                write(STDERR, ERROR_OPEN_FILE, string_len(ERROR_OPEN_FILE));
                _exit(1);
            }
            dup2(input_fd, STDIN);
            close(input_fd);

        }else if(stage > 0){

            dup2(pipefd[(stage - 1) * 2], STDIN);

        }

        /*Process output redirection*/
        if(stage == job->num_stages - 1 && job->outfile_path != NULL){
            output_fd = open(job->outfile_path, O_WRONLY | O_CREAT | O_TRUNC);

            if(output_fd < 0){
                write(STDERR, ERROR_OPEN_FILE, string_len(ERROR_OPEN_FILE));
                _exit(1);
            }
            dup2(output_fd, STDOUT);
            close(output_fd);
        }else if(stage < job->num_stages - 1){

            dup2(pipefd[stage * 2 + 1], STDOUT);

        }

        for (i = 0; i < (job->num_stages -1) * 2; i++){
            close(pipefd[i]);
        }

        if(execve(job->pipeline[stage].argv[0], job->pipeline[stage].argv, NULL) == -1){
            write(STDERR, ERROR_EXECVE, string_len(ERROR_EXECVE));
            _exit(1);
        }

    }else if(pid > 0){ /*Parent starts here*/

        return pid;

    } 
    write(STDERR, ERROR_FORK_FAILED, string_len(ERROR_FORK_FAILED));
    exit(1);

}
