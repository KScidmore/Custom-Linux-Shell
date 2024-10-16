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
#include <sys/types.h>
#include <unistd.h>
#include "commands.h"
#include "errorcodes.h"
#include "jobs.h"
#include "memory.h"
#include "prompt.h"
#include "stringlib.h"

/* globals */



int main() {

    Command command;
    Job job;

    while (1) {
        init_job(&job);
        get_job(&job);

        if(string_comp(job.pipeline[0].argv[0], "exit") == 1){
            break;
        }
        
        run_job(&job);
    }

    return 0;
}